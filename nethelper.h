#ifndef NETHELPER_H
#define NETHELPER_H

#include <QUrl>
#include <QFtp>
#include <QHttp>

class NetHelper
{
public:
    NetHelper();

    static void DownloadFile(QUrl URI, QString DownloadDir, QString FileName);

    static QString LoadInfo(QUrl URI, QString AppName);

    static void ReadListing(QUrl URI);

    static QString CheckUpdates();

    static void GetUpdates(QString Version);
};

#endif // NETHELPER_H
