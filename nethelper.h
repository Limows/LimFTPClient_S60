#ifndef NETHELPER_H
#define NETHELPER_H

#include "paramshelper.h"
#include "mainwindow.h"

#include <QUrl>
#include <QFtp>
#include <QHttp>
#include <QWidget>
#include <QtCore/QCoreApplication>
#include <QDesktopWidget>

class NetHelper : public QObject
{
    Q_OBJECT

public:
    NetHelper();

    void DownloadFile(QUrl URI, QString DownloadDir, QString FileName);

    QString LoadInfo(QUrl URI, QString AppName);

    void ReadListing(QUrl URI);

    QString CheckUpdates();

    void GetUpdates(QString Version);

public slots:
    void AddToList(const QUrlInfo &UriInfo);

    void FtpCommandFinished(const int Id, const bool IsError);

    void FtpDone(bool Bool);

signals:
    void done(bool IsError);

private:
    QFtp *Ftp;
};

#endif // NETHELPER_H
