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
