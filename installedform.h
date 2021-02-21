#ifndef INSTALLEDFORM_H
#define INSTALLEDFORM_H

#include "paramshelper.h"
#include "systemhelper.h"

#include <QWidget>
#include <QObject>
#include <QAction>
#include <QTextCodec>
#include <QDesktopWidget>

namespace Ui {
    class InstalledForm;
}

class InstalledForm : public QWidget
{
    Q_OBJECT

public:
    explicit InstalledForm(QWidget *parent = 0);

    ~InstalledForm();

private slots:
    void on_DeleteAction_triggered();

    void on_PropAction_triggered();

private:
    Ui::InstalledForm *ui;

signals:
    void closed();
};

#endif // INSTALLEDFORM_H
