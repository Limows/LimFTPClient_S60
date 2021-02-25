#ifndef APPDIALOG_H
#define APPDIALOG_H

#include "paramshelper.h"
#include "nethelper.h"
#include "iohelper.h"
#include "systemhelper.h"

#include <QTextCodec>
#include <QWidget>
#include <QDesktopWidget>
#include <QMessageBox>

namespace Ui {
    class AppDialog;
}

class AppDialog : public QWidget
{
    Q_OBJECT

private:
    Ui::AppDialog *ui;
    QString AppName;

public:
    explicit AppDialog(QString AppName = "Application", QWidget *parent = 0);

    ~AppDialog();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    void InitLayout();

signals:
    void closed();

private slots:
    void on_DownloadButton_clicked();

    void on_BackButton_clicked();

    void on_Downloading_Complete(bool IsError);

    void on_Extracting_Complete(bool IsError, QString ExtractedFilePath);

    void on_Installing_Complete(bool IsError);
};

#endif // APPDIALOG_H
