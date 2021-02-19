#include "appdialog.h"
#include "ui_appdialog.h"

AppDialog::AppDialog(QString CurrentAppName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppDialog)
{
    ui->setupUi(this);

    const QRect ScreenRect = QApplication::desktop()->screenGeometry();
    int height = ScreenRect.height();
    int width = ScreenRect.width();
    QRect *FormRect = new QRect(0, 0, width, height);

    this->setGeometry(*FormRect);
    ui->ContentLayout->setGeometry(*FormRect);
    ui->gridLayoutWidget->setGeometry(*FormRect);
    ui->TitleLabel->setAutoFillBackground(true);

    this->AppName = CurrentAppName;

    ui->TitleLabel->setText(this->AppName);

    this->AppName = CurrentAppName.replace(" ", "_");

    ParamsHelper::AppURI = QUrl(ParamsHelper::SystemURI.toString() + "/" + this->AppName);
}

AppDialog::~AppDialog()
{
    delete ui;
}

void AppDialog::on_DownloadButton_clicked()
{
    ParamsHelper::CurrentURI = ParamsHelper::AppURI;
    NetHelper *FtpNetHelper = new NetHelper(ParamsHelper::CurrentURI);
    QEventLoop pause;

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    this->setCursor(Qt::WaitCursor);
    ui->StatusLabel->setText(tr("��� ��������"));

    connect(FtpNetHelper, SIGNAL(done(bool)), this, SLOT(on_Downloading_Complete(bool)));
    connect(FtpNetHelper, SIGNAL(done(bool)), &pause, SLOT(quit()));

    if (!ParamsHelper::DownloadPath.isEmpty() && !ParamsHelper::DownloadPath.isNull())
    {
        FtpNetHelper->DownloadFile(ParamsHelper::DownloadPath, this->AppName + ".zip");
    }
    else
    {
        QMessageBox::warning(this, tr("��������������"), tr("����������� ���� ��� ���������� �����"), QMessageBox::Ok);
        ui->StatusLabel->setText(tr("������ ��� ��������"));
        disconnect(this, SLOT(on_Downloading_Complete(bool)));
        return;
    }

    pause.exec();

    IOHelper *ZipHelper = new IOHelper();

    this->setCursor(Qt::WaitCursor);
    ui->StatusLabel->setText(tr("��� ����������"));

    connect(ZipHelper, SIGNAL(done(bool)), this, SLOT(on_Extracting_Complete(bool)));

    ZipHelper->ExtractToDirectory(ParamsHelper::DownloadPath + "/" + this->AppName + ".zip", ParamsHelper::DownloadPath + "/" + this->AppName);
}

void AppDialog::on_Downloading_Complete(bool IsError)
{
    if (!IsError)
    {
        ui->StatusLabel->setText(tr("������� ���������"));
    }
    else
    {
        ui->StatusLabel->setText(tr("������ ��� ��������"));
        QMessageBox::critical(this, tr("������"), tr("�� ������� ������������ � �������"), QMessageBox::Ok);
    }

    this->setCursor(Qt::ArrowCursor);
}

void AppDialog::on_Extracting_Complete(bool IsError)
{
    if (!IsError)
    {
        ui->StatusLabel->setText(tr("������� �����������"));
    }
    else
    {
        ui->StatusLabel->setText(tr("������ ��� ����������"));
    }

    this->setCursor(Qt::ArrowCursor);
}

void AppDialog::on_BackButton_clicked()
{
    this->close();
    emit closed();
}
