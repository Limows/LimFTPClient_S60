#ifndef PARAMSDIALOG_H
#define PARAMSDIALOG_H

#include "paramshelper.h"
#include "iohelper.h"
#include "systemhelper.h"

#include <QWidget>
#include <QDesktopWidget>
#include <QObject>
#include <QFileDialog>
#include <QPalette>
#include <QTextCodec>
#include <QMessageBox>

namespace Ui {
    class ParamsDialog;
}

class ParamsDialog : public QWidget
{
    Q_OBJECT

private:
    Ui::ParamsDialog *ui;

public:
    explicit ParamsDialog(QWidget *parent = 0);

    virtual ~ParamsDialog();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    QString OpenDirDialog();

    QString CheckDirectory(QString Path);

    void InitLayout();

signals:
    void closed();

private slots:
    void on_ExitAction_triggered();

    void on_OpenDirButton_clicked();

    void on_SaveButton_clicked();
};

#endif // PARAMSDIALOG_H
