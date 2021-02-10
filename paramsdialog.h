#ifndef PARAMSDIALOG_H
#define PARAMSDIALOG_H

#include <QtGui/QDialog>
#include <QObject>

namespace Ui {
    class ParamsDialog;
}

class ParamsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ParamsDialog(QWidget *parent = 0);
    virtual ~ParamsDialog();

private slots:
    void on_ParamsDialog_destroyed();

    void on_ExitAction_triggered();

private:
    Ui::ParamsDialog *ui;

};

#endif // PARAMSDIALOG_H
