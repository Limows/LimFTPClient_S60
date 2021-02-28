#ifndef SYSTEMHELPER_H
#define SYSTEMHELPER_H

#include "f32file.h"
#include "e32const.h"
#include "paramshelper.h"

#include <QString>
#include <QList>
#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QTextStream>
#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QRect>
//#include <SWInstApi.h>
//#include <SWInstDefs.h>

class SystemHelper : public QObject
{
    Q_OBJECT

public:
    SystemHelper();

    static QList<QString> GetInstalledApps();

    static QString GetInstallDir(QString AppName);

    void AppInstall(QString AppPath, QString InstallPath, QString AppName, bool Overwrite);

    void AppUninstall(QString AppName);

    static ulong GetStorageSpace(QString Path);

    static QList<QString> GetAllStorages();

    static void GetSystemInfo();

    static QRect* GetScreenRect();

signals:
    void done(bool IsError);
};

#endif // SYSTEMHELPER_H
