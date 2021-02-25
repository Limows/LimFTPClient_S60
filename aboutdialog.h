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

private:
    Ui::AboutDialog *ui;

public:
    explicit AboutDialog(QWidget *parent = 0);

    ~AboutDialog();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    void InitLayout();

signals:
    void closed();

private slots:
    void on_OKButton_clicked();
};

#endif // ABOUTDIALOG_H
