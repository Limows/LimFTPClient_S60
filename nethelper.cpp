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
    this->Ftp = new QFtp(this);
    QObject::connect(this->Ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(FtpCommandFinished(int,bool)));
    QObject::connect(this->Ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(AddToList(QUrlInfo)));
    QObject::connect(this->Ftp, SIGNAL(done(bool)), this, SLOT(FtpDone(bool)));

    this->Ftp->setTransferMode(QFtp::Passive);
    this->Ftp->connectToHost(URI.host(), URI.port());
    this->Ftp->login(URI.userName(), "");
    QString FtpPath = URI.path();
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

    if (IsError)
    {
        this->Ftp->close();
        emit done(IsError);
    }
}

void NetHelper::FtpDone(bool IsError)
{
    emit done(IsError);
}

QString NetHelper::CheckUpdates()
{

}

void NetHelper::GetUpdates(QString Version)
{
    return;
}
