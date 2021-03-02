#include "paramsdialog.h"
#include "ui_paramsdialog.h"

ParamsDialog::ParamsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsDialog)
{
    ui->setupUi(this);

    InitLayout();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    ui->AutoInstallBox->setChecked(ParamsHelper::IsAutoInstall);
    ui->OverwriteDirsBox->setChecked(ParamsHelper::IsOverwrite);
    ui->RmPackageBox->setChecked(ParamsHelper::IsRmPackage);
    ui->DownloadPathBox->setText(ParamsHelper::DownloadPath);
    ui->TempSizeBox->setText(QString::number(ParamsHelper::BytesToMegs(ParamsHelper::TempSize)));
    ui->UsedTempSizeLabel->setText(tr("Занято сейчас: ") + QString::number(ParamsHelper::BytesToMegs(IOHelper::GetDirectorySize(ParamsHelper::TempPath))) + tr(" МБ"));

    QList<QString> DrivesNames = SystemHelper::GetAllStorages();
    ParamsHelper::InstallPath = DrivesNames[0];
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

QString ParamsDialog::CheckDirectory(QString Path)
{
    QDir Directory = QDir(Path);

    if(Directory.exists())
    {
        return Path;
    }
    else
    {
        QMessageBox::StandardButton Result = QMessageBox::warning(this, tr("Предупреждение"), tr("Такая директория не существует.\n\nСоздать?"), QMessageBox::Yes|QMessageBox::No);

        if (Result == QMessageBox::Yes)
        {
            if(Directory.mkpath(Path))
            {
                return Path;
            }
            else
            {
                QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось создать директорию"), QMessageBox::Ok);
                return "";
            }
        }
        else return "";
    }
}

void ParamsDialog::on_SaveButton_clicked()
{
    ParamsHelper::DownloadPath = CheckDirectory(ui->DownloadPathBox->text());
    ParamsHelper::IsAutoInstall = ui->AutoInstallBox->isChecked();
    ParamsHelper::IsOverwrite = ui->OverwriteDirsBox->isChecked();
    ParamsHelper::IsRmPackage = ui->RmPackageBox->isChecked();

    if (ParamsHelper::InstallPath.isEmpty() || ParamsHelper::InstallPath.isNull())
    {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Выберите место для установки"), QMessageBox::Ok);
        return;
    }

    if (ParamsHelper::DownloadPath.isEmpty() || ParamsHelper::DownloadPath.isNull())
    {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Путь не может быть пустым"), QMessageBox::Ok);
        return;
    }

    if (ui->TempSizeBox->text().isEmpty() || ui->TempSizeBox->text().isNull() || ui->TempSizeBox->text().toDouble() == 0)
    {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Не задан размер хранилища"), QMessageBox::Ok);
        return;
    }
    else
    {
        ParamsHelper::TempSize = ParamsHelper::MegsToBytes(ui->TempSizeBox->text().toDouble());
    }

    this->close();
    emit closed();
}


void ParamsDialog::InitLayout()
{
    const QRect ScreenRect = QApplication::desktop()->screenGeometry();

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
    ui->SystemTabLayout->setGeometry(*TabRect);
    ui->gridLayoutWidget_4->setGeometry(*TabRect);
}

void ParamsDialog::resizeEvent(QResizeEvent *event)
{
    InitLayout();
}
