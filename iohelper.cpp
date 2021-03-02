#include "iohelper.h"

IOHelper::IOHelper()
{

}

void IOHelper::ExtractAsync()
{
    QuaZip UnZip(this->Compressed);
    QDir ExtractedDir;
    bool IsError = false;

    UnZip.open(QuaZip::mdUnzip);

    ExtractedDir.mkpath(this->Extracted);

    for(bool FileExist = UnZip.goToFirstFile(); FileExist; FileExist=UnZip.goToNextFile())
    {
        QuaZipFile CompressedFile(&UnZip);
        QString FileName = CompressedFile.getActualFileName();
        QFile *ExtractedFile = new QFile(this->Extracted + QDir::separator() + FileName);

        CompressedFile.open(QIODevice::ReadOnly);
        ExtractedFile->open(QFile::ReadWrite);

        ExtractedFile->write(CompressedFile.readAll());

        CompressedFile.close();
        ExtractedFile->close();
    }

    UnZip.close();

    emit unzip_done(IsError, this->Extracted);
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
    if (ParamsHelper::ConfigPath.isNull() || ParamsHelper::ConfigPath.isEmpty())
    {
        ParamsHelper::ConfigPath = GetConfigPath("/");
    }

    QFile *ConfigFile = new QFile(ParamsHelper::ConfigPath + "AppManager.conf");
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
    ParamsHelper::TempPath = QDir::currentPath() + QDir::separator() + "Temp";

    if (ParamsHelper::ConfigPath.isNull() || ParamsHelper::ConfigPath.isEmpty())
    {
        ParamsHelper::ConfigPath = GetConfigPath("/");
    }

    QFile *ConfigFile = new QFile(ParamsHelper::ConfigPath + "AppManager.conf");
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
    if (ParamsHelper::ConfigPath.isNull() || ParamsHelper::ConfigPath.isEmpty())
    {
        ParamsHelper::ConfigPath = GetConfigPath("/");
    }

    QFile *ConfigFile = new QFile(ParamsHelper::ConfigPath + "AppManager.conf");

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
            return Path + dir + QDir::separator();
        }

        if (dir == "Data" || dir == "data")
        {
            return GetConfigPath(QDir::separator() + dir + QDir::separator());
        }
    }

    return "/";
}

ulong IOHelper::GetDirectorySize(QString Path)
{
    qint64 Size = 0;
    QDir Directory = QDir(Path);

    if (Directory.exists())
    {
        QDir::Filters FilesFilter = QDir::Files|QDir::System|QDir::Hidden;
        QDir::Filters DirsFilter = QDir::Dirs|QDir::NoDotAndDotDot|QDir::System|QDir::Hidden;

        QList<QString> Files = Directory.entryList(FilesFilter);

        foreach(QString file, Files)
        {
            QFileInfo FileInfo(Directory, file);
            Size += FileInfo.size();
        }

        QList<QString> Directories = Directory.entryList(DirsFilter);

        foreach(QString dir, Directories)
        {
            Size += GetDirectorySize(Path + QDir::separator() + dir);
        }

        return (uint)Size;
    }
    else
    {
        return 0;
    }
}
