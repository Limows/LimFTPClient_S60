#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    const QRect ScreenRect = QApplication::desktop()->screenGeometry();

    this->setGeometry(ScreenRect);

    ui->ContentLayout->setGeometry(ScreenRect);

    ui->layoutWidget->setGeometry(ScreenRect);

    ui->TitleLabel->setAutoFillBackground(true);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    ui->labelProductName->setText("Limowski App Manager");
    ui->labelVersion->setText(tr("������: ") + QString(APP_VERSION));
    ui->labelBuild->setText(tr("������ ��: ") + QString(BUILDDATE));
    ui->labelCompanyName->setText(tr("�����: ") + QString(APP_VENDOR));
    ui->textBoxDescription_5->setText("Small Application Manager for Symbian S60");
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
