#include "mainwindow.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow.setWindowIcon(QIcon(":/icons/logo.ico"));

    mainWindow.showMaximized();
    return app.exec();
}
