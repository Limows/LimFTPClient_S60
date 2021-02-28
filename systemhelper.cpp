#include "systemhelper.h"

SystemHelper::SystemHelper()
{

}

void SystemHelper::AppInstall(QString AppPath, QString InstallPath, QString AppName, bool Overwrite)
{

}

void SystemHelper::AppUninstall(QString AppName)
{

}

ulong SystemHelper::GetStorageSpace(QString Path)
{
    TChar DriveChar = Path.at(0).toAscii();
    TInt Drive = 0;
    RFs FileSystem;
    TVolumeInfo VolumeInfo;

    //User::LeaveIfError(FileSystem.Connect());

    //CleanupClosePushL(FileSystem);

    FileSystem.Connect();

    FileSystem.CharToDrive(DriveChar, Drive);

    FileSystem.Volume(VolumeInfo, Drive);

    ulong DriveFreeSpace = (ulong)VolumeInfo.iFree;

    //CleanupStack::PopAndDestroy(&FileSystem);

    return DriveFreeSpace;
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
