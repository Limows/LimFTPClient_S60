#include "installedform.h"
#include "ui_installedform.h"

InstalledForm::InstalledForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstalledForm)
{
    ui->setupUi(this);
}

InstalledForm::~InstalledForm()
{
    delete ui;

}

void InstalledForm::on_DeleteAction_triggered()
{

}
