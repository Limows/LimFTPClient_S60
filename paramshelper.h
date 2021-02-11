#ifndef PARAMSHELPER_H
#define PARAMSHELPER_H

#include "list"

#include <QString>

class ParamsHelper
{
public:
    //static Uri ServerURI = new Uri("ftp://anon@limowski.xyz:2121");
    //static public Uri CurrentURI;
    //static public Uri SystemURI;
    //static public Uri AppURI;
    static QString DownloadPath;
    static QString InstallPath;
    static QString ConfigPath;
    static int OSVersion;
    static std::list<std::string> AppsList;
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
