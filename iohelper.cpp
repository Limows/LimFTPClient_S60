#include "iohelper.h"

IOHelper::IOHelper()
{

}

QString IOHelper::ExtractToDirectory(QString CompressedFilePath, QString ExtractedFilePath)
{
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

    emit done(IsError);

    return ExtractedFilePath;
}
