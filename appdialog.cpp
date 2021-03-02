#include "appdialog.h"
#include "ui_appdialog.h"

AppDialog::AppDialog(QString CurrentAppName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppDialog)
{
    ui->setupUi(this);

    InitLayout();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    ui->TitleLabel->setText(CurrentAppName);
    ui->NameLabel->setText(CurrentAppName);
    ui->StatusLabel->setText(QString());

    this->AppName = CurrentAppName.replace(' ', '_');

    ParamsHelper::AppURI = QUrl(ParamsHelper::SystemURI.toString() + "/" + this->AppName);
}

AppDialog::~AppDialog()
{
    delete ui;
}

void AppDialog::on_DownloadButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    ui->StatusLabel->setText(tr("Идёт загрузка"));

    if (!ParamsHelper::DownloadPath.isEmpty() && !ParamsHelper::DownloadPath.isNull())
    {
        ParamsHelper::CurrentURI = ParamsHelper::AppURI;
        NetHelper *FtpNetHelper = new NetHelper(ParamsHelper::CurrentURI);

        connect(FtpNetHelper, SIGNAL(done(bool)), this, SLOT(on_Downloading_Complete(bool)));

        FtpNetHelper->DownloadFile(ParamsHelper::DownloadPath, this->AppName + ".zip");
    }
    else
    {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Отсутствует путь для сохранения файла"), QMessageBox::Ok);
        ui->StatusLabel->setText(tr("Ошибка при загрузке"));
    }
}

void AppDialog::on_Downloading_Complete(bool IsError)
{
    if (!IsError)
    {
        ui->StatusLabel->setText(tr("Успешно загружено"));
        this->setCursor(Qt::ArrowCursor);

        QMessageBox::StandardButton Result;

        //if (!ParamsHelper::IsAutoInstall)
        //{
        //    Result = QMessageBox::question(this, tr("Сообщение"), tr("Установить?"), QMessageBox::Yes|QMessageBox::No);
        //}
        //else
        //{
            Result = QMessageBox::Yes;
        //}

        if (Result == QMessageBox::Yes)
        {

            this->setCursor(Qt::WaitCursor);
            ui->StatusLabel->setText(tr("Идёт распаковка"));

            IOHelper *ZipHelper = new IOHelper();

            connect(ZipHelper, SIGNAL(unzip_done(bool, QString)), this, SLOT(on_Extracting_Complete(bool, QString)));

            ZipHelper->ExtractToDirectory(ParamsHelper::DownloadPath + QDir::separator() + this->AppName + ".zip", ParamsHelper::DownloadPath + QDir::separator() + this->AppName);
        }
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
        ui->StatusLabel->setText(tr("Ошибка при загрузке"));
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось подключиться к серверу"), QMessageBox::Ok);
    }
}

void AppDialog::on_Extracting_Complete(bool IsError, QString ExtractedFilePath)
{
    if (!IsError)
    {
        ui->StatusLabel->setText(tr("Успешно распаковано"));
        this->setCursor(Qt::ArrowCursor);

        this->setCursor(Qt::WaitCursor);
        ui->StatusLabel->setText(tr("Идёт установка"));

        SystemHelper *InstallHelper = new SystemHelper();

        connect(InstallHelper, SIGNAL(done(bool)), this, SLOT(on_Installing_Complete(bool)));

        InstallHelper->AppInstall(ExtractedFilePath, ParamsHelper::InstallPath, ParamsHelper::IsOverwrite);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
        ui->StatusLabel->setText(tr("Ошибка при распаковке"));
    }

}

void AppDialog::on_Installing_Complete(bool IsError)
{
    if (!IsError)
    {
        ui->StatusLabel->setText(tr("Успешно установлено"));
    }
    else
    {
        ui->StatusLabel->setText(tr("Ошибка при установке"));
    }

    this->setCursor(Qt::ArrowCursor);
}

void AppDialog::on_BackButton_clicked()
{
    this->close();
    emit closed();
}

void AppDialog::InitLayout()
{
    const QRect ScreenRect = QApplication::desktop()->screenGeometry();

    this->setGeometry(ScreenRect);
    ui->ContentLayout->setGeometry(ScreenRect);
    ui->gridLayoutWidget->setGeometry(ScreenRect);

    ui->TitleLabel->setAutoFillBackground(true);
}

void AppDialog::resizeEvent(QResizeEvent *event)
{
    InitLayout();
}
