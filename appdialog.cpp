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
    ui->LogoView->setGeometry(ui->LogoView->x(), ui->LogoView->y(), ui->LogoView->width(), ui->LogoView->width());
    ui->TitleLabel->setAutoFillBackground(true);
    ui->TitleLabel->setText(CurrentAppName);

    this->AppName = CurrentAppName.replace(' ', '_');

    ParamsHelper::AppURI = QUrl(ParamsHelper::SystemURI.toString() + "/" + this->AppName);
}

AppDialog::~AppDialog()
{
    delete ui;
}

void AppDialog::on_DownloadButton_clicked()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    this->setCursor(Qt::WaitCursor);
    ui->StatusLabel->setText(tr("��� ��������"));

    if (!ParamsHelper::DownloadPath.isEmpty() && !ParamsHelper::DownloadPath.isNull())
    {
        ParamsHelper::CurrentURI = ParamsHelper::AppURI;
        NetHelper *FtpNetHelper = new NetHelper(ParamsHelper::CurrentURI);

        connect(FtpNetHelper, SIGNAL(done(bool)), this, SLOT(on_Downloading_Complete(bool)));

        FtpNetHelper->DownloadFile(ParamsHelper::DownloadPath, this->AppName + ".zip");
    }
    else
    {
        QMessageBox::warning(this, tr("��������������"), tr("����������� ���� ��� ���������� �����"), QMessageBox::Ok);
        ui->StatusLabel->setText(tr("������ ��� ��������"));
    }
}

void AppDialog::on_Downloading_Complete(bool IsError)
{
    if (!IsError)
    {
        ui->StatusLabel->setText(tr("������� ���������"));
        this->setCursor(Qt::ArrowCursor);

        this->setCursor(Qt::WaitCursor);
        ui->StatusLabel->setText(tr("��� ����������"));

        IOHelper *ZipHelper = new IOHelper();

        connect(ZipHelper, SIGNAL(done(bool)), this, SLOT(on_Extracting_Complete(bool)));

        ZipHelper->ExtractToDirectory(ParamsHelper::DownloadPath + "/" + this->AppName + ".zip", ParamsHelper::DownloadPath + "/" + this->AppName);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
        ui->StatusLabel->setText(tr("������ ��� ��������"));
        QMessageBox::critical(this, tr("������"), tr("�� ������� ������������ � �������"), QMessageBox::Ok);
    }
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
