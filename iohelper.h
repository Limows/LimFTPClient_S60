#ifndef IOHELPER_H
#define IOHELPER_H

#include "quazip/quazip.h"
#include "quazip/quazipfile.h"

#include <QString>
#include <QObject>
#include <QtCore>
#include <QByteArray>
#include <QFile>
#include <QDir>



class IOHelper : public QObject
{
    Q_OBJECT

public:
    IOHelper();

    void LoadParameters();

    QString ExtractToDirectory(QString CompressedFilePath, QString ExtractedFilePath);

    void CleanBuffer();

    void SaveParameters();

    void RemoveParameters();

signals:
    void done(bool IsError);

private:
    QString GetConfigPath();
};

#endif // IOHELPER_H
