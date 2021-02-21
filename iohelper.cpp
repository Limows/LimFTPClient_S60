#include "iohelper.h"

IOHelper::IOHelper()
{

}

void IOHelper::ExtractAsync()
{
    QString CompressedFilePath = this->Compressed;
    QString ExtractedFilePath = this->Extracted;
    QuaZip UnZip(CompressedFilePath);          
    QDir ExtractedDir;
    bool IsError = false;

    UnZip.open(QuaZip::mdUnzip);

    ExtractedDir.mkpath(ExtractedFilePath);

    for(bool FileExist = UnZip.goToFirstFile(); FileExist; FileExist=UnZip.goToNextFile())
    {
        QuaZipFile CompressedFile(&UnZip);
        QString FileName = CompressedFile.getActualFileName();
        QFile *ExtractedFile = new QFile(ExtractedFilePath + "/" + FileName);

        CompressedFile.open(QIODevice::ReadOnly);
        ExtractedFile->open(QFile::ReadWrite);

        ExtractedFile->write(CompressedFile.readAll());

        CompressedFile.close();
        ExtractedFile->close();
    }

    UnZip.close();

    emit unzip_done(IsError, ExtractedFilePath);
}

void IOHelper::ExtractToDirectory(QString CompressedFilePath, QString ExtractedFilePath)
{
    QThread *UnZipThread = new QThread(this);

    this->Compressed = CompressedFilePath;
    this->Extracted = ExtractedFilePath;
    moveToThread(UnZipThread);

    connect(UnZipThread, SIGNAL(started()), this, SLOT(ExtractAsync()));

    UnZipThread->start();
}

void IOHelper::SaveParameters()
{
    QFile *ConfigFile = new QFile(GetConfigPath("/") + "AppManager.conf");
    ConfigFile->open(QFile::WriteOnly);

    QDataStream Config(ConfigFile);

    Config << ParamsHelper::IsAutoInstall;
    Config << ParamsHelper::IsOverwrite;
    Config << ParamsHelper::IsRmPackage;
    Config << ParamsHelper::InstallPath;
    Config << ParamsHelper::DownloadPath;
    Config << (quint64)ParamsHelper::TempSize;

    ConfigFile->close();
}

void IOHelper::LoadParameters()
{
    QFile *ConfigFile = new QFile(GetConfigPath("/") + "AppManager.conf");
    ConfigFile->open(QFile::ReadOnly);

    QDataStream Config(ConfigFile);

    Config >> ParamsHelper::IsAutoInstall;
    Config >> ParamsHelper::IsOverwrite;
    Config >> ParamsHelper::IsRmPackage;
    Config >> ParamsHelper::InstallPath;
    Config >> ParamsHelper::DownloadPath;
    Config >> (quint64&)ParamsHelper::TempSize;

    ConfigFile->close();
}

void IOHelper::RemoveParameters()
{
    QFile *ConfigFile = new QFile(GetConfigPath("/") + "AppManager.conf");

    ConfigFile->remove();
}

QString IOHelper::GetConfigPath(QString Path)
{
    QDir *ConfigDir = new QDir(Path);

    QList<QString> DirsList = ConfigDir->entryList();

    foreach(QString dir, DirsList)
    {
        if (dir == ".config")
        {
            return Path + ".config/";
        }

        if (dir == "Data" || dir == "data")
        {
            return GetConfigPath("/" + dir + "/");
        }
    }

    return "/";
}
