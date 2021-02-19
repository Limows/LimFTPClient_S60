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
    QString GetConfigPath();
};

#endif // IOHELPER_H
