#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    const QRect ScreenRect = QApplication::desktop()->screenGeometry(this);

    int height = ScreenRect.height();
    int width = ScreenRect.width();
    QRect *FormRect = new QRect(0, 0, width, (int)(height*0.92));

    this->setGeometry(*FormRect);
    ui->GridLayout->setGeometry(*FormRect);
    ui->gridLayoutWidget->setGeometry(*FormRect);

    QString ServerURIString = ParamsHelper::ServerURI.toString();
    QString Repository = SetRepository();

    ParamsHelper::SystemURI = QUrl(ServerURIString + Repository);

    connect(ui->AppsListWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(on_AppsListWidget_itemClicked(QListWidgetItem*)));

    BeginConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif

}

void MainWindow::on_ParamsAction_triggered()
{
    ParamsDialog *NewParamsDialog = new ParamsDialog();

    NewParamsDialog->showFullScreen();

    connect(NewParamsDialog, SIGNAL(closed()), this, SLOT(on_Closing_Dialog()));
}

void MainWindow::on_RefreshAction_triggered()
{
    BeginConnect();
}

void MainWindow::on_HelpAction_triggered()
{
    QMessageBox::information(this, tr("������"), tr("��� ������ ���������� �������� �� ��� �������� � ������"), QMessageBox::Ok);
}

void MainWindow::on_AboutAction_triggered()
{
    AboutDialog *NewAboutDialog = new AboutDialog();

    NewAboutDialog->setWindowIcon(QIcon(":/icons/logo.ico"));

    NewAboutDialog->showFullScreen();

    connect(NewAboutDialog, SIGNAL(closed()), this, SLOT(on_Closing_Dialog()));
}

void MainWindow::on_Closing_Dialog()
{
    Qt::WindowFlags flags;
    flags |= Qt::WindowSoftkeysVisibleHint;
    flags &= ~Qt::WindowSoftkeysRespondHint;

    this->setWindowFlags(flags);
    this->showFullScreen();
}

void MainWindow::on_UpdateAction_triggered()
{
    try
    {
        NetHelper *HttpNetHelper = new NetHelper(QUrl("http://limowski.xyz:80"), NetHelper::HTTP);

        QString Version = HttpNetHelper->CheckUpdates("/downloads/LimFTPClient/Symbian_S60/LimFTPClientVersion.txt");

        Version = Version.replace("\n", "");

        QMessageBox::StandardButton Result;

        Result = QMessageBox::question(this, tr("���������"), tr("��������?\n\n������� ������: ") + Version, QMessageBox::Yes|QMessageBox::No);

        if (Result == QMessageBox::Yes)
        {
            if (!ParamsHelper::DownloadPath.isEmpty() && !ParamsHelper::DownloadPath.isNull())
            {
                HttpNetHelper->GetUpdates("/downloads/LimFTPClient/Symbian_S60/LimFTPClient.sis");
            }
            else
            {
                QMessageBox::warning(this, tr("��������������"), tr("����������� ���� ��� ���������� �����"), QMessageBox::Ok);
            }
        }
    }
    catch(int)
    {
        QMessageBox::critical(this, tr("������"), tr("�� ������� ��������"), QMessageBox::Ok);
    }
}

void MainWindow::BeginConnect()
{
    ParamsHelper::CurrentURI = ParamsHelper::SystemURI;
    NetHelper *FtpNetHelper = new NetHelper(ParamsHelper::CurrentURI);

    ui->AppsListWidget->clear();

    this->setCursor(Qt::WaitCursor);

    connect(FtpNetHelper, SIGNAL(done(bool)), this, SLOT(on_Listing_Complete(bool)));

    FtpNetHelper->ReadListing();
}

void MainWindow::on_Listing_Complete(bool IsError)
{
    if (!IsError)
    {
        for (int i = 0; i < ParamsHelper::AppsList.length(); i++)
        {
            ui->AppsListWidget->insertItem(i, ParamsHelper::AppsList[i]);
        }
    }
    else
    {
        QMessageBox::critical(this, tr("������"), tr("�� ������� ������������ � �������"), QMessageBox::Ok);
    }

    ParamsHelper::AppsList.clear();

    this->setCursor(Qt::ArrowCursor);
}

QString MainWindow::SetRepository()
{
    ParamsHelper::OSVersion = QSysInfo::s60Version();

    switch (ParamsHelper::OSVersion)
    {
    case QSysInfo::SV_S60_3_1:
        return "/Symbian_S60v3";
        break;

    case QSysInfo::SV_S60_3_2:
        return "/Symbian_S60v3";
        break;

    case QSysInfo::SV_S60_5_0:
        return "/Symbian_S60v5";
        break;

    case QSysInfo::SV_S60_5_1:
        return "/Symbian_S60v5";
        break;

    case QSysInfo::SV_S60_5_2:
        return "/Symbian_S60v5";
        break;

    default:
        return "/Symbian^3";
    }
}

void MainWindow::on_AppsListWidget_itemClicked(QListWidgetItem *item)
{
    QString AppName = item->text();
    AppDialog *NewAppDialog = new AppDialog(AppName);

    connect(NewAppDialog, SIGNAL(closed()), this, SLOT(on_Closing_Dialog()));

    NewAppDialog->showFullScreen();
}

void MainWindow::on_InstalledAction_triggered()
{
    InstalledForm *NewInstalledForm = new InstalledForm();

    Qt::WindowFlags flags;
    flags |= Qt::WindowSoftkeysVisibleHint;
    flags &= ~Qt::WindowSoftkeysRespondHint;

    NewInstalledForm->setWindowFlags(flags);
    NewInstalledForm->setWindowIcon(QIcon(":/icons/logo.ico"));

    NewInstalledForm->showFullScreen();

    connect(NewInstalledForm, SIGNAL(closed()), this, SLOT(on_Closing_Dialog()));
}
