#ifndef SYSTEMHELPER_H
#define SYSTEMHELPER_H

#include "f32file.h"
#include "e32const.h"
#include "paramshelper.h"
#include "SWInstApi.h"
#include "SWInstDefs.h"
#include "apgcli.h"
#include "logger.h"

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
#include <QDesktopServices>
#include <QMap>
#include <QProcess>

class SystemHelper : public QObject
{
    Q_OBJECT

public:
    SystemHelper();

    static QMap<QString, uint> GetInstalledApps();

    static QString GetInstallDir(uint AppUid);

    void AppInstall(QString AppPath, QString InstallPath, bool Overwrite);

    void UpdateInstall(QString UpdatePath);

    void AppUninstall(uint AppUid);

    static ulong GetStorageSpace(QString Path);

    static QList<QString> GetAllStorages();

    static void GetSystemInfo();

    static QRect* GetScreenRect();

    void WriteLog(QString LogString);

signals:
    void done(bool IsError);
};

#endif // SYSTEMHELPER_H
