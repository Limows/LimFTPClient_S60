#ifndef NETHELPER_H
#define NETHELPER_H

#include "paramshelper.h"

#include <QUrl>
#include <QFtp>
#include <QHttp>
#include <QObject>
#include <QBuffer>
#include <QEventLoop>
#include <QFile>
#include <QDir>

class NetHelper : public QObject
{
    Q_OBJECT

public:
    enum NetType
    {
        FTP,
        HTTP
    };

public:
    NetHelper();

    NetHelper(QUrl URI, NetType Type = FTP);

    void DownloadFile(QString DownloadDir, QString FileName);

    QString LoadInfo(QString AppName);

    void ReadListing();

    QString CheckUpdates(QString Source);

    void GetUpdates(QString Source);

private slots:
    void AddToList(const QUrlInfo &UriInfo);

    void FtpCommandFinished(const int Id, const bool IsError);

    void HttpCommandFinished(const int Id, const bool IsError);

    void FtpDone(bool IsError);

    void HttpDone(bool IsError);

signals:
    void done(bool IsError);

private:
    QFtp *Ftp;
    QHttp *Http;
    QUrl URI;
    QBuffer *Reader;
    QFile *Update;
    QFile *Downloaded;
};

#endif // NETHELPER_H
