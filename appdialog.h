#ifndef APPDIALOG_H
#define APPDIALOG_H

#include <QTextCodec>
#include <QWidget>
#include <QtCore/QCoreApplication>
#include <QDesktopWidget>

namespace Ui {
    class AppDialog;
}

class AppDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AppDialog(QWidget *parent = 0, QString AppName = "AppName");
    ~AppDialog();

private slots:
    void on_DownloadButton_clicked();

private:
    Ui::AppDialog *ui;
};

#endif // APPDIALOG_H
