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
