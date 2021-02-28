#include "mainwindow.h"
#include "paramsdialog.h"
#include "aboutdialog.h"
#include "iohelper.h"

#include <QtGui/QApplication>
#include <Qt>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    Qt::WindowFlags flags;
    flags |= Qt::WindowSoftkeysVisibleHint;
    flags &= ~Qt::WindowSoftkeysRespondHint;

    SystemHelper::GetSystemInfo();

    mainWindow.setWindowFlags(flags);
    mainWindow.setWindowIcon(QIcon(":/icons/logo.ico"));

    mainWindow.showFullScreen();

    IOHelper::LoadParameters();

    int appresult = app.exec();

    IOHelper::SaveParameters();

    return appresult;
}
