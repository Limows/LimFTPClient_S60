#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paramsdialog.h"
#include "paramshelper.h"
#include "aboutdialog.h"
#include "nethelper.h"

#include <QtGui/QMainWindow>
#include <QTextCodec>
#include <QtCore/QCoreApplication>
#include <QMessageBox>
#include <QScreen>
#include <QDesktopWidget>
#include <QUrl>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);

    virtual ~MainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

private slots:
    void on_ParamsAction_triggered();

    void on_RefreshAction_triggered();

    void on_HelpAction_triggered();

    void on_AboutAction_triggered();

    void on_UpdateAction_triggered();

    void on_Closing_Dialog();

private:
    Ui::MainWindow *ui;

private:
    void Connect();
};

#endif // MAINWINDOW_H
