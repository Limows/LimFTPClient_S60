#include "installedform.h"
#include "ui_installedform.h"

InstalledForm::InstalledForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstalledForm)
{
    InitComponents();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    QMenu* Menu = new QMenu(this);

    Menu->addAction(tr("Удалить"), this, SLOT(on_DeleteAction_triggered()));
    Menu->addAction(tr("Свойства"), this, SLOT(on_PropAction_triggered()));

    QAction *RightOption = new QAction("Exit", this);
    RightOption->setMenu(Menu);
    RightOption->setSoftKeyRole(QAction::NegativeSoftKey);
    QObject::connect(RightOption, SIGNAL(triggered()), this, SLOT(close()));
    this->addAction(RightOption);

    QAction *LeftOption = new QAction("Options", this);
    LeftOption->setMenu(Menu);
    LeftOption->setSoftKeyRole(QAction::PositiveSoftKey);
    this->addAction(LeftOption);

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
    SystemHelper *UninstallHelper = new SystemHelper();
    uint AppUid = 0;
    QString AppName = ui->InstalledListWidget->currentItem()->text();

    if (!AppName.isNull() && !AppName.isEmpty())
    {
        connect(UninstallHelper, SIGNAL(done(bool)), this, SLOT(on_Uninstalling_Complete(bool)));

        AppUid = this->InstalledMap.value(AppName);
        UninstallHelper->AppUninstall(AppUid);
    }
    else
    {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Приложение не выбрано"), QMessageBox::Ok);
    }
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

void InstalledForm::on_Uninstalling_Complete(bool IsError)
{
    if (IsError)
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось удалить приложение"), QMessageBox::Ok);
    }
    else
    {
        this->InstalledMap = SystemHelper::GetInstalledApps();

        if (!this->InstalledMap.isEmpty())
        {
            int i = 0;

            ui->InstalledListWidget->clear();

            foreach (QString app_name, InstalledMap.keys())
            {
                ui->InstalledListWidget->insertItem(i, app_name);
                i++;
            }
        }
    }
}
