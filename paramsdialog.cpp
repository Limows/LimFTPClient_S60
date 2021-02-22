#include "paramsdialog.h"
#include "ui_paramsdialog.h"

ParamsDialog::ParamsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsDialog)
{
    ui->setupUi(this);

    const QRect ScreenRect = QApplication::desktop()->screenGeometry();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    this->setGeometry(ScreenRect);
    ui->ContentLayout->setGeometry(ScreenRect);
    ui->gridLayoutWidget->setGeometry(ScreenRect);

    ui->TitleLabel->setAutoFillBackground(true);
    QColor BackColor = ui->TabWidget->palette().color(QPalette::Background);
    QPalette palette = this->palette();
    palette.setColor(this->backgroundRole(), BackColor);
    this->setPalette(palette);

    QRect TabWidgetRect = ui->TabWidget->geometry();
    QRect *TabRect = new QRect(0, 0, TabWidgetRect.width() - 3, TabWidgetRect.height() - 20);

    ui->DownloadTabLayout->setGeometry(*TabRect);
    ui->gridLayoutWidget_2->setGeometry(*TabRect);
    ui->InstallTabLayout->setGeometry(*TabRect);
    ui->gridLayoutWidget_3->setGeometry(*TabRect);
    ui->BufferTabLayout->setGeometry(*TabRect);
    ui->gridLayoutWidget_4->setGeometry(*TabRect);

    ui->AutoInstallBox->setChecked(ParamsHelper::IsAutoInstall);
    ui->OverwriteDirsBox->setChecked(ParamsHelper::IsOverwrite);
    ui->RmPackageBox->setChecked(ParamsHelper::IsRmPackage);
    ui->DownloadPathBox->setText(ParamsHelper::DownloadPath);
    ui->TempSizeBox->setText(QString::number(ParamsHelper::BytesToMegs(ParamsHelper::TempSize)));
    ui->UsedTempSizeLabel->setText(tr("Занято сейчас: ") + QString::number(ParamsHelper::BytesToMegs(IOHelper::GetDirectorySize(ParamsHelper::TempPath))) + tr(" МБ"));

    QList<QString> DrivesNames = SystemHelper::GetAllStorages();
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
    ui->DownloadPathBox->setText(OpenDirDialog());
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
    ParamsHelper::DownloadPath = ui->DownloadPathBox->text();
    ParamsHelper::IsAutoInstall = ui->AutoInstallBox->isChecked();
    ParamsHelper::IsOverwrite = ui->OverwriteDirsBox->isChecked();
    ParamsHelper::IsRmPackage = ui->RmPackageBox->isChecked();
    ParamsHelper::TempSize = ParamsHelper::MegsToBytes(ui->TempSizeBox->text().toDouble());

    this->close();
    emit closed();
}
