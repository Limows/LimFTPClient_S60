#ifndef INSTALLEDFORM_H
#define INSTALLEDFORM_H

#include <QWidget>

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

private:
    Ui::InstalledForm *ui;

signals:
    void closed();
};

#endif // INSTALLEDFORM_H
