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

uint SystemHelper::GetStorageSpace(QString Path)
{
    RFs FileSystem;
    TDriveInfo DriveInfo;

    FileSystem.Connect();

    FileSystem.Drive(DriveInfo);

    uint DriveAtributes = (uint)DriveInfo.iDriveAtt;

    DriveAtributes;
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
