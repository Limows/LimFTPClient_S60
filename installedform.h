#ifndef INSTALLEDFORM_H
#define INSTALLEDFORM_H

#include "paramshelper.h"
#include "systemhelper.h"

#include <QWidget>
#include <QObject>
#include <QAction>
#include <QTextCodec>
#include <QDesktopWidget>
#include <QMap>

namespace Ui {
    class InstalledForm;
}

class InstalledForm : public QWidget
{
    Q_OBJECT

private:
    Ui::InstalledForm *ui;

public:
    QMap<QString, uint> InstalledMap;

public:
    explicit InstalledForm(QWidget *parent = 0);

    ~InstalledForm();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    void InitLayout(QRect* FormRect);

    void InitComponents();

signals:
    void closed();

private slots:
    void on_DeleteAction_triggered();

    void on_PropAction_triggered();
};

#endif // INSTALLEDFORM_H
