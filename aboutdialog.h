#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QTextCodec>
#include <QWidget>
#include <QDesktopWidget>

namespace Ui {
    class AboutDialog;
}

class AboutDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);

    ~AboutDialog();

signals:
    void closed();

private slots:
    void on_OKButton_clicked();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
