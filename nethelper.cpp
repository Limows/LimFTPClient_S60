#include "nethelper.h"


NetHelper::NetHelper()
{

}

void NetHelper::DownloadFile(QUrl URI, QString DownloadDir, QString FileName)
{
    return;
}

QString NetHelper::LoadInfo(QUrl URI, QString AppName)
{

}

void NetHelper::ReadListing(QUrl URI)
{
    QFtp Ftp;
    Ftp.setTransferMode(QFtp::Passive);
    Ftp.connectToHost(URI.host(), URI.port());
    Ftp.login(URI.userName(), "");
    Ftp.list();
    Ftp.close();
    return;
}

QString NetHelper::CheckUpdates()
{

}

void NetHelper::GetUpdates(QString Version)
{
    return;
}
