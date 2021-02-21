#ifndef SYSTEMHELPER_H
#define SYSTEMHELPER_H

#include <QString>
#include <QList>
#include <QObject>
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

signals:
    void done(bool IsError);
};

#endif // SYSTEMHELPER_H
