#include "nethelper.h"


NetHelper::NetHelper()
{

}

NetHelper::NetHelper(QUrl URI)
{
    this->URI = URI;
    this->Ftp = new QFtp(this);

    connect(this->Ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(FtpCommandFinished(int,bool)));
    connect(this->Ftp, SIGNAL(done(bool)), this, SLOT(FtpDone(bool)));

    this->Ftp->setTransferMode(QFtp::Passive);
    this->Ftp->connectToHost(this->URI.host(), this->URI.port());
    this->Ftp->login(this->URI.userName(), "");
}

void NetHelper::DownloadFile(QString DownloadDir, QString FileName)
{
    return;
}

QString NetHelper::LoadInfo(QString AppName)
{

}

void NetHelper::ReadListing()
{
    QString FtpPath = this->URI.path();

    connect(this->Ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(AddToList(QUrlInfo)));

    this->Ftp->cd(FtpPath);
    this->Ftp->list();
    this->Ftp->close();
}

void NetHelper::AddToList(const QUrlInfo &UriInfo)
{
    QString AppName = UriInfo.name();

    if (AppName.indexOf('.') == -1)
    {
        ParamsHelper::AppsList.append(AppName.replace('_',' '));
    }
}

void NetHelper::FtpCommandFinished(const int Id, const bool IsError)
{
    QFtp::Command Command = Ftp->currentCommand();
    QString Status = "";

    if (Command == QFtp::Close)
    {
        Status = "Done";
    }
}

void NetHelper::FtpDone(bool IsError)
{
    QFtp::Command Command = Ftp->currentCommand();
    QString Status = "";

    if (Command == QFtp::Close)
    {
        Status = "Done";
    }

    emit done(IsError);
}

QString NetHelper::CheckUpdates()
{

}

void NetHelper::GetUpdates(QString Version)
{
    return;
}
