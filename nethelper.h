#ifndef NETHELPER_H
#define NETHELPER_H

#include "paramshelper.h"
#include "mainwindow.h"

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

    void DownloadFile(QUrl URI, QString DownloadDir, QString FileName);

    QString LoadInfo(QUrl URI, QString AppName);

    void ReadListing();

    QString CheckUpdates();

    void GetUpdates(QString Version);

public slots:
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
