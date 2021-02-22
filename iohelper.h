#ifndef IOHELPER_H
#define IOHELPER_H

#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include "paramshelper.h"

#include <QString>
#include <QObject>
#include <QtCore>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDataStream>
#include <QList>
#include <QThread>



class IOHelper : public QObject
{
    Q_OBJECT

public:
    IOHelper();

    static void LoadParameters();

    static void CleanBuffer();

    static void SaveParameters();

    static void RemoveParameters();

    void ExtractToDirectory(QString CompressedFilePath, QString ExtractedFilePath);

    static ulong GetDirectorySize(QString Path);

private:
    QString Compressed;

    QString Extracted;

private slots:
    void ExtractAsync();

signals:
    void unzip_done(bool IsError, QString ExtractedFilePath);

private:
    static QString GetConfigPath(QString Path);

    void ExtractAsync(QString CompressedFilePath, QString ExtractedFilePath);
};

#endif // IOHELPER_H
