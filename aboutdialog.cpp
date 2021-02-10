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

    this->addAction(RightOption);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_ExitAction_triggered()
{
    this->close();
}
