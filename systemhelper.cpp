#include "systemhelper.h"

SystemHelper::SystemHelper()
{

}

void SystemHelper::AppInstall(QString AppPath, QString InstallPath, QString AppName, bool Overwrite)
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

    Options.iOCSP = SwiUI::EPolicyNotAllowed;
    Options.iDrive = InstallPath.at(0).toAscii();
    Options.iUntrusted = SwiUI::EPolicyAllowed;
    Options.iCapabilities = SwiUI::EPolicyAllowed;
    Options.iPackageInfo = SwiUI::EPolicyNotAllowed;
    Options.iKillApp = SwiUI::EPolicyAllowed;

    OptionsPckg = Options;

    TPtrC16 BufFileName(reinterpret_cast<const TUint16*>(FileName.utf16()));
    Installer.Connect();
    Error = Installer.SilentInstall(BufFileName, OptionsPckg);
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

void SystemHelper::AppUninstall(QString AppName)
{
    SwiUI::RSWInstLauncher Uninstaller;
    SwiUI::TUninstallOptions Options;
    SwiUI::TUninstallOptions OptionsPckg;
    int Error = 0;
    uint AppUid = 0;

    Options.iKillApp = SwiUI::EPolicyAllowed;

    OptionsPckg = Options;

    Uninstaller.Connect();
    //Error = Uninstaller.SilentUninstall(TUid::Uid(AppUid), OptionsPckg, SwiUI::KSisMimeType);
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
