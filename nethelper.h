#ifndef NETHELPER_H
#define NETHELPER_H

#include "paramshelper.h"

#include <QUrl>
#include <QFtp>
#include <QHttp>
#include <QObject>

class NetHelper : public QObject
{
    Q_OBJECT

public:
    NetHelper();

    NetHelper(QUrl URI);

    void DownloadFile(QString DownloadDir, QString FileName);

    QString LoadInfo(QString AppName);

    void ReadListing();

    QString CheckUpdates();

    void GetUpdates(QString Version);

private slots:
    void AddToList(const QUrlInfo &UriInfo);

    void FtpCommandFinished(const int Id, const bool IsError);

    void FtpDone(bool IsError);

signals:
    void done(bool IsError);

private:
    QFtp *Ftp;
    QUrl URI;
};

#endif // NETHELPER_H
