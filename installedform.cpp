#include "installedform.h"
#include "ui_installedform.h"

InstalledForm::InstalledForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstalledForm)
{
    InitComponents();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    QAction *RightOption = new QAction("Exit", this);
    RightOption->setSoftKeyRole(QAction::NegativeSoftKey);
    QObject::connect(RightOption, SIGNAL(triggered()), this, SLOT(close()));

    QAction *LeftOption = new QAction(tr("Удалить"), this);
    LeftOption->setSoftKeyRole(QAction::PositiveSoftKey);
    QObject::connect(LeftOption, SIGNAL(triggered()), this, SLOT(on_DeleteAction_triggered()));

    QList<QAction*> ActionsList = QList<QAction*>();
    ActionsList.append(RightOption);
    ActionsList.append(LeftOption);

    this->addActions(ActionsList);

    ui->MemLabel->setText(tr("Доступно памяти: ") + QString::number(ParamsHelper::BytesToMegs(SystemHelper::GetStorageSpace(ParamsHelper::InstallPath))) + tr(" МБ"));

    this->InstalledMap = SystemHelper::GetInstalledApps();

    if (!this->InstalledMap.isEmpty())
    {
        int i = 0;

        foreach (QString app_name, InstalledMap.keys())
        {
            ui->InstalledListWidget->insertItem(i, app_name);
            i++;
        }
    }
}

InstalledForm::~InstalledForm()
{
    delete ui;
}

void InstalledForm::on_DeleteAction_triggered()
{

}

void InstalledForm::on_PropAction_triggered()
{

}

void InstalledForm::InitLayout(QRect *FormRect)
{
    this->setGeometry(*FormRect);
    ui->ContentLayout->setGeometry(*FormRect);
    ui->gridLayoutWidget->setGeometry(*FormRect);
}

void InstalledForm::resizeEvent(QResizeEvent *event)
{
    QRect *FormRect = SystemHelper::GetScreenRect();

    InitLayout(FormRect);
}

void InstalledForm::InitComponents()
{
    QRect *FormRect = SystemHelper::GetScreenRect();

    ui->setupUi(this);

    InitLayout(FormRect);
}
