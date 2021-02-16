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
    explicit AppDialog(QString AppName = "Application", QWidget *parent = 0);
    ~AppDialog();

private slots:
    void on_DownloadButton_clicked();

    void on_BackButton_clicked();

signals:
    void closed();

private:
    Ui::AppDialog *ui;
};

#endif // APPDIALOG_H
