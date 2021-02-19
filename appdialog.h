#ifndef APPDIALOG_H
#define APPDIALOG_H

#include "paramshelper.h"
#include "nethelper.h"
#include "iohelper.h"

#include <QTextCodec>
#include <QWidget>
#include <QtCore/QCoreApplication>
#include <QDesktopWidget>
#include <QMessageBox>

namespace Ui {
    class AppDialog;
}

class AppDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AppDialog(QString CurrentAppName = "Application", QWidget *parent = 0);
    ~AppDialog();

private slots:
    void on_DownloadButton_clicked();

    void on_BackButton_clicked();

    void on_Downloading_Complete(bool IsError);

    void on_Extracting_Complete(bool IsError);

signals:
    void closed();

private:
    Ui::AppDialog *ui;
    QString AppName;
};

#endif // APPDIALOG_H
