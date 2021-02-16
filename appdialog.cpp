#include "appdialog.h"
#include "ui_appdialog.h"

AppDialog::AppDialog(QWidget *parent, QString AppName) :
    QWidget(parent),
    ui(new Ui::AppDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(AppName);

    const QRect ScreenRect = QApplication::desktop()->screenGeometry();
    int height = ScreenRect.height();
    int width = ScreenRect.width();

    QRect *FormRect = new QRect(0, 0, width, height);

    this->setGeometry(*FormRect);

    ui->ContentLayout->setGeometry(*FormRect);

    ui->gridLayoutWidget->setGeometry(*FormRect);

    ui->TitleLabel->setAutoFillBackground(true);
}

AppDialog::~AppDialog()
{
    delete ui;
}

void AppDialog::on_DownloadButton_clicked()
{

}
