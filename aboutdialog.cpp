#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QAction *RightOption = new QAction("OK", this);
    RightOption->setSoftKeyRole(QAction::NegativeSoftKey);
    QObject::connect(RightOption, SIGNAL(triggered()), this, SLOT(close()));

    //const QRect ScreenRect = QApplication::desktop()->availableGeometry();
    const QRect ScreenRect = QDialog::geometry();
    int height = ScreenRect.height();
    int width = ScreenRect.width();

    QRect *FormRect = new QRect(0, 0, width, height);

    this->setGeometry(*FormRect);

    ui->GridLayout->setGeometry(*FormRect);

    ui->gridLayoutWidget->setGeometry(*FormRect);

    this->addAction(RightOption);

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

void AboutDialog::on_ExitAction_triggered()
{
    this->close();
}
