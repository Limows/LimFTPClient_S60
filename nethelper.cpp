#include "nethelper.h"


NetHelper::NetHelper()
{

}

NetHelper::NetHelper(QUrl URI, bool IsFTP)
{
    if (IsFTP)
    {
        this->URI = URI;
        this->Ftp = new QFtp(this);

        connect(this->Ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(FtpCommandFinished(int,bool)));
        connect(this->Ftp, SIGNAL(done(bool)), this, SLOT(FtpDone(bool)));

        this->Ftp->setTransferMode(QFtp::Passive);
        this->Ftp->connectToHost(this->URI.host(), this->URI.port());
        this->Ftp->login(this->URI.userName(), "");
    }
    else
    {
        this->URI = URI;
        this->Http = new QHttp(this);
        this->Reader = new QBuffer(this);
        this->Update = new QFile(ParamsHelper::DownloadPath + "/Update.sis");

        //connect(this->Http, SIGNAL(requestFinished(int,bool)), this, SLOT(HttpCommandFinished(int,bool)));
        //connect(this->Http, SIGNAL(done(bool)), SLOT(HttpDone(bool)));

        this->Http->setHost(this->URI.host());
    }
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

QString NetHelper::CheckUpdates(QString Source)
{
    QEventLoop pause;

    connect(this->Http, SIGNAL(done(bool)), &pause, SLOT(quit()));

    Reader->open(QBuffer::ReadWrite);
    this->Http->get(Source, this->Reader);
    this->Http->closeConnection();
    pause.exec();

    return Reader->buffer();
}

void NetHelper::GetUpdates(QString Source)
{
    QEventLoop pause;

    connect(this->Http, SIGNAL(done(bool)), &pause, SLOT(quit()));

    Update->open(QFile::ReadWrite);
    this->Http->get(Source, this->Update);
    this->Http->closeConnection();
    pause.exec();
}

void NetHelper::HttpDone(bool IsError)
{
    emit done(IsError);
}

void NetHelper::HttpCommandFinished(const int Id, const bool IsError)
{

}
