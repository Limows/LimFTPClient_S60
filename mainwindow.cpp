#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //const QRect ScreenRect = QApplication::desktop()->availableGeometry();
    const QRect ScreenRect = QApplication::desktop()->screenGeometry();
    int height = ScreenRect.height();
    int width = ScreenRect.width();

    QRect *FormRect = new QRect(0, 0, width, height);

    this->setGeometry(*FormRect);

    ui->GridLayout->setGeometry(*FormRect);

    ui->gridLayoutWidget->setGeometry(*FormRect);

    QString ServerURIString = ParamsHelper::ServerURI.toString();

    ParamsHelper::SystemURI = QUrl(ServerURIString + "/Symbian_S60v3");
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

    NewParamsDialog->showMaximized();
}

void MainWindow::on_RefreshAction_triggered()
{
    Connect();
}

void MainWindow::on_HelpAction_triggered()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    QMessageBox HelpBox;

    HelpBox.setText(tr("Помощь"));
    HelpBox.setIcon(QMessageBox::Information);
    HelpBox.setInformativeText(tr("Для выбора приложения кликните по его названию в списке"));

    HelpBox.exec();
}

void MainWindow::on_AboutAction_triggered()
{
    AboutDialog *NewAboutDialog = new AboutDialog();

    NewAboutDialog->showMaximized();
}

void MainWindow::on_UpdateAction_triggered()
{

}

void MainWindow::Connect()
{
    NetHelper::ReadListing(ParamsHelper::SystemURI);
}
