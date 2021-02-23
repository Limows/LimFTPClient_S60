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
    static QString TempPath;
    static QSysInfo::SymbianVersion OSVersion;
    static QList<QString> AppsList;
    static bool IsAutoInstall;
    static bool IsRmPackage;
    static bool IsOverwrite;
    static ulong TempSize;

public:
    ParamsHelper();

    static double BytesToMegs(ulong Bytes);

    static ulong MegsToBytes(double Megs);
};

#endif // PARAMSHELPER_H
