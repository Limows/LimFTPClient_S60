#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    const QRect ScreenRect = QApplication::desktop()->screenGeometry();
    int height = ScreenRect.height();
    int width = ScreenRect.width();

    QRect *FormRect = new QRect(0, 0, width, height);

    this->setGeometry(*FormRect);

    ui->ContentLayout->setGeometry(*FormRect);

    ui->widget->setGeometry(*FormRect);

    ui->TitleLabel->setAutoFillBackground(true);

    //ui->->setGeometry(*FormRect);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    ui->labelProductName->setText("Limowski App Manager");
    ui->labelVersion->setText(tr("Версия: ") + QString(APP_VERSION));
    ui->labelBuild->setText(tr("Сборка от: ") + QString(BUILDDATE));
    ui->labelCompanyName->setText(tr("Автор: ") + QString(APP_VENDOR));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_OKButton_clicked()
{
    this->close();
    emit closed();
}

void AboutDialog::on_AboutDialog_destroyed()
{

}
