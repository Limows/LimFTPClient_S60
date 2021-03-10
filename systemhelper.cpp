#include "systemhelper.h"

SystemHelper::SystemHelper()
{

}

void SystemHelper::AppInstall(QString AppPath, QString InstallPath, bool Overwrite)
{
    QStringList NameFilters;
    QDir AppDir(AppPath);
    QFileInfoList SisFilesList;
    SwiUI::RSWInstLauncher Installer;
    SwiUI::TInstallOptions Options;
    SwiUI::TInstallOptionsPckg OptionsPckg;
    QString FileName;
    int Error = 0;

    NameFilters << "*.sis";
    NameFilters << "*.sisx";
    NameFilters << "*.jar";

    SisFilesList = AppDir.entryInfoList(NameFilters,QDir::Files);

    if (SisFilesList.length() > 0)
    {
        FileName = SisFilesList.at(0).absoluteFilePath().replace("/", "\\");
    }
    else
    {
        emit done(true);
        return;
    }

    if (Overwrite)
    {
        Options.iUpgrade = SwiUI::EPolicyAllowed;
        Options.iOverwrite = SwiUI::EPolicyAllowed;
        Options.iUpgradeData = SwiUI::EPolicyAllowed;
    }
    else
    {
        Options.iUpgrade = SwiUI::EPolicyNotAllowed;
        Options.iOverwrite = SwiUI::EPolicyNotAllowed;
        Options.iUpgradeData = SwiUI::EPolicyNotAllowed;
    }

    Options.iOCSP = SwiUI::EPolicyAllowed;
    Options.iIgnoreOCSPWarnings = SwiUI::EPolicyAllowed;
    Options.iOptionalItems = SwiUI::EPolicyAllowed;
    Options.iDrive = InstallPath.at(0).toAscii();
    Options.iUntrusted = SwiUI::EPolicyAllowed;
    Options.iCapabilities = SwiUI::EPolicyAllowed;
    Options.iPackageInfo = SwiUI::EPolicyAllowed;
    Options.iKillApp = SwiUI::EPolicyAllowed;
    Options.iDownload = SwiUI::EPolicyAllowed;

    OptionsPckg = Options;

    TPtrC16 BufFileName(reinterpret_cast<const TUint16*>(FileName.utf16()));
    Installer.Connect();
    if (ParamsHelper::IsAutoInstall)
    {
        Error = Installer.SilentInstall(BufFileName, OptionsPckg);
    }
    else
    {
        Error = Installer.Install(BufFileName, OptionsPckg);
    }
    Installer.Close();

    if (Error == 0)
    {
        emit done(false);
    }
    else
    {
        emit done(true);
    }
}

void SystemHelper::AppUninstall(uint AppUid)
{
    SwiUI::RSWInstLauncher Uninstaller;
    SwiUI::TUninstallOptions Options;
    SwiUI::TUninstallOptionsPckg OptionsPckg;
    int Error = 0;

    Options.iKillApp = SwiUI::EPolicyAllowed;

    OptionsPckg = Options;

    Uninstaller.Connect();

    if (ParamsHelper::IsAutoInstall)
    {
        Error = Uninstaller.SilentUninstall(TUid::Uid(AppUid), OptionsPckg, SwiUI::KSisxMimeType());
    }
    else
    {
        Error = Uninstaller.Uninstall(TUid::Uid(AppUid), SwiUI::KSisxMimeType());

        if (Error != 0)
        {
            Error = Uninstaller.Uninstall(TUid::Uid(AppUid), SwiUI::KSisMimeType());

            if (Error != 0)
            {
                Error = Uninstaller.Uninstall(TUid::Uid(AppUid), SwiUI::KJarxMIMEType);
            }
        }
    }

    Uninstaller.Close();

    if (Error == 0)
    {
        emit done(false);
    }
    else
    {
        emit done(true);
    }
}

ulong SystemHelper::GetStorageSpace(QString Path)
{
    if (!Path.isEmpty() && !Path.isNull())
    {
        TChar DriveChar = Path.at(0).toAscii();
        TInt Drive = 0;
        RFs FileSystem;
        TVolumeInfo VolumeInfo;
        ulong DriveFreeSpace = 0;
        int Error;

        Error = FileSystem.Connect();
        //CleanupClosePushL(FileSystem);

        if (Error == 0)
        {
            FileSystem.CharToDrive(DriveChar, Drive);
            FileSystem.Volume(VolumeInfo, Drive);
            DriveFreeSpace = (ulong)VolumeInfo.iFree;
            return DriveFreeSpace;
        }
        else
        {
            return 0;
        }
        //CleanupStack::PopAndDestroy(&FileSystem);
    }
    else
    {
        return 0;
    }
}

QList<QString> SystemHelper::GetAllStorages()
{
    QFileInfoList Drives = QDir::drives();
    QList<QString> DrivesNames = QList<QString>();

    foreach(QFileInfo drive, Drives)
    {
        QString DriveName = drive.path();
        DrivesNames.append(DriveName);
    }

    return DrivesNames;
}

void SystemHelper::GetSystemInfo()
{
    QString CurrentPath = "/";
    QFile *SysInfoFile = new QFile(CurrentPath + QDir::separator() + "AppManager.log");
    SysInfoFile->open(QFile::WriteOnly);

    QTextStream SysInfo(SysInfoFile);
    const QRect ScreenRect = QApplication::desktop()->screenGeometry();
    const QRect AvailableRect = QApplication::desktop()->availableGeometry();

    SysInfo << "ScreenGeometry: " << ScreenRect.width() << "x" << ScreenRect.height() << endl;
    SysInfo << "AvailableGeometry: " << AvailableRect.width() << "x" << AvailableRect.height() << endl;
    SysInfo << "InstallPath: " << ParamsHelper::InstallPath << endl;
    SysInfo << "SymbianVersion: ";

    switch (ParamsHelper::OSVersion)
    {
    case QSysInfo::SV_9_2:
        SysInfo << "SV_9_2" << endl;
        break;

    case QSysInfo::SV_9_3:
        SysInfo << "SV_9_3" << endl;
        break;

    case QSysInfo::SV_9_4:
        SysInfo << "SV_9_4" << endl;
        break;

    case QSysInfo::SV_SF_2:
        SysInfo << "SV_SF_2" << endl;
        break;

    case QSysInfo::SV_SF_3:
        SysInfo << "SV_SF_3" << endl;
        break;

    case QSysInfo::SV_SF_4:
        SysInfo << "SV_SF_4" << endl;
        break;

    case QSysInfo::SV_Unknown:
        SysInfo << "SV_Unknown" << endl;
        break;

    default:
        SysInfo << "SV_None" << endl;
    }

    SysInfoFile->close();
}

QRect* SystemHelper::GetScreenRect()
{
    const QRect ScreenRect = QApplication::desktop()->screenGeometry();
    const QRect AvailableRect = QApplication::desktop()->availableGeometry();

    if (ScreenRect.height() == AvailableRect.height() && ScreenRect.width() == AvailableRect.width())
    {
        return new QRect(0, 0, ScreenRect.width(), (int)(ScreenRect.height()*0.92));
    }
    else
    {
        return new QRect(0, 0, AvailableRect.width(), AvailableRect.height());
    }
}

QMap<QString, uint> SystemHelper::GetInstalledApps()
{
    RApaLsSession AppListSession;
    QMap<QString, uint> InstalledMap;
    TApaAppInfo AppInfo;
    int Error = 0;

    Error = AppListSession.Connect();

    if (Error == 0)
    {
        AppListSession.GetAllApps();

        while (AppListSession.GetNextApp(AppInfo) == 0)
        {
            TApaAppCapabilityBuf CapabilityBuf;
            TApaAppCapability Capability;
            QString AppName = QString::fromUtf16(AppInfo.iCaption.Ptr(), AppInfo.iCaption.Length());

            AppListSession.GetAppCapability(CapabilityBuf, AppInfo.iUid);
            Capability = CapabilityBuf();
            AppName = AppName.trimmed();

            if (AppName.length() > 0 && !Capability.iAppIsHidden)
            {
                InstalledMap.insert(AppName, (uint)AppInfo.iUid.iUid);
            }
        }
    }
    return InstalledMap;
}

void SystemHelper::UpdateInstall(QString UpdatePath)
{
    QProcess *Install = new QProcess(this);

    UpdatePath = UpdatePath.replace("/", "\\");
    Install->startDetached("\"" + UpdatePath + "\"");
    //QDesktopServices::openUrl(QUrl("file:///" + UpdatePath));
}

void SystemHelper::WriteLog(QString LogString)
{
    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);

    _LIT(KLogFile, "c:\\log.txt");
    RFile file;
    file.Replace(fs, KLogFile, EFileWrite);
    CleanupClosePushL(file);

    CLogger *logger = CLogger::NewL(file, CLogger::ELevelAll & ~CLogger::ELevelDebug); // Prints all messages except Debug
    CleanupStack::PushL(logger);
    LoggerStatic::SetLogger(logger); // Set default logger

    // You may use either 16 or 8-bit descriptors
    LOG(_L16("Simple message in 16bit descriptor (uncategorized)"));
    // or
    LOG(_L8("Simple message in 8bit descriptor (uncategorized)"));

    DEBUG(_L("This is debug message")); // This kind of message currently disabled in logger settings
    INFO(_L("This is info message"));
    WARNING(_L("This is warning message"));
    _LIT(KErrTxt, "Not Found");
    ERROR(_L("This is formatted error message with code: %d (%S)"), 404, &KErrTxt);

    CleanupStack::PopAndDestroy(3, &fs); // logger + file + fs

    LOG(_L("Logger already has been destroyed and this message won`t be included to the log file :("));
}
