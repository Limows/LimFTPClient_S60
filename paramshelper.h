#ifndef PARAMSHELPER_H
#define PARAMSHELPER_H

#include <QString>
#include <QUrl>
#include <QList>
#include <QSysInfo>

class ParamsHelper
{
public:
    static QUrl ServerURI;
    static QUrl CurrentURI;
    static QUrl SystemURI;
    static QUrl AppURI;
    static QString DownloadPath;
    static QString InstallPath;
    static QString ConfigPath;
    static QSysInfo::S60Version OSVersion;
    static QList<QString> AppsList;
    static bool IsThreadAlive;
    static bool IsThreadError;
    static bool IsThreadWaiting;
    //static Exception ThreadException;
    static QString ThreadMessage;
    static bool IsAutoInstall;
    static bool IsRmPackage;
    static bool IsOverwrite;
    static bool IsUninstalling;

public:
    ParamsHelper();

    static double BytesToMegs(ulong Bytes);
};

#endif // PARAMSHELPER_H
