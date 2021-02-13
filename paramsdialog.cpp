#include "paramsdialog.h"
#include "ui_paramsdialog.h"

ParamsDialog::ParamsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsDialog)
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
}

ParamsDialog::~ParamsDialog()
{
    delete ui;
}

void ParamsDialog::on_ExitAction_triggered()
{
    this->close();
}

void ParamsDialog::on_OpenDirButton_clicked()
{
    ui->DownloadPathBox->insert(OpenDirDialog());
}

QString ParamsDialog::OpenDirDialog()
{
    QFileDialog OpenDir;
    OpenDir.setFileMode(QFileDialog::Directory);
    OpenDir.setOption(QFileDialog::ShowDirsOnly);

    int Result = OpenDir.exec();

    if (Result)
    {
        return OpenDir.selectedFiles()[0];
    }
    else return "";
}

void ParamsDialog::on_SaveButton_clicked()
{
    this->close();
    emit closed();
}
