#ifndef PARAMSDIALOG_H
#define PARAMSDIALOG_H

#include "paramshelper.h"

#include <QWidget>
#include <QtCore/QCoreApplication>
#include <QDesktopWidget>
#include <QObject>
#include <QFileDialog>
#include <QPalette>

namespace Ui {
    class ParamsDialog;
}

class ParamsDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ParamsDialog(QWidget *parent = 0);

    virtual ~ParamsDialog();

signals:
    void closed();

private slots:
    void on_ExitAction_triggered();

    void on_OpenDirButton_clicked();

    void on_SaveButton_clicked();

private:
    Ui::ParamsDialog *ui;

private:
    QString OpenDirDialog();

};

#endif // PARAMSDIALOG_H
