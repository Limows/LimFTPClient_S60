#include "installedform.h"
#include "ui_installedform.h"

InstalledForm::InstalledForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstalledForm)
{
    ui->setupUi(this);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    const QRect ScreenRect = QApplication::desktop()->screenGeometry(this);

    int height = ScreenRect.height();
    int width = ScreenRect.width();
    QRect *FormRect = new QRect(0, 0, width, (int)(height*0.92));

    this->setGeometry(*FormRect);
    ui->ContentLayout->setGeometry(*FormRect);
    ui->gridLayoutWidget->setGeometry(*FormRect);

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

    ui->MemLabel->setText(tr("Доступно памяти: ") + QString::number(SystemHelper::GetStorageSpace(ParamsHelper::InstallPath)) + tr(" МБ"));
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
