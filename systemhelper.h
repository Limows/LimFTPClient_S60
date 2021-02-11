#ifndef SYSTEMHELPER_H
#define SYSTEMHELPER_H

#include "list"

#include <QString>

class SystemHelper
{
public:
    SystemHelper();

    static std::list<std::string> GetInstalledApps();

    static QString GetInstallDir(QString AppName);

    static bool AppInstall(QString AppPath, QString InstallPath, QString AppName, bool Overwrite);

    static bool AppUninstall(QString AppName);
};

#endif // SYSTEMHELPER_H
