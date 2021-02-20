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
#include <QDir>
#include <QDataStream>
#include <QList>



class IOHelper : public QObject
{
    Q_OBJECT

public:
    IOHelper();

    static void LoadParameters();

    QString ExtractToDirectory(QString CompressedFilePath, QString ExtractedFilePath);

    void CleanBuffer();

    static void SaveParameters();

    static void RemoveParameters();

signals:
    void done(bool IsError);

private:
    static QString GetConfigPath(QString Path);
};

#endif // IOHELPER_H
