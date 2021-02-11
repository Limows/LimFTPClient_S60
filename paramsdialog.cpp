#include "paramsdialog.h"
#include "ui_paramsdialog.h"

ParamsDialog::ParamsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamsDialog)
{
    ui->setupUi(this);

    QAction *RightOption = new QAction("Exit", this);
    RightOption->setSoftKeyRole(QAction::NegativeSoftKey);
    QObject::connect(RightOption, SIGNAL(triggered()), this, SLOT(close()));

    this->addAction(RightOption);
}

ParamsDialog::~ParamsDialog()
{
    delete ui;
}

void ParamsDialog::on_ParamsDialog_destroyed()
{

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
