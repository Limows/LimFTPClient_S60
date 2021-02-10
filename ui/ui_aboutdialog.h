/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created: Wed 10. Feb 23:24:33 2021
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QAction *ExitAction;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QString::fromUtf8("AboutDialog"));
        AboutDialog->resize(240, 270);
        AboutDialog->setMinimumSize(QSize(240, 270));
        ExitAction = new QAction(AboutDialog);
        ExitAction->setObjectName(QString::fromUtf8("ExitAction"));
        ExitAction->setMenuRole(QAction::TextHeuristicRole);
        ExitAction->setSoftKeyRole(QAction::NegativeSoftKey);

        retranslateUi(AboutDialog);

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        ExitAction->setText(QApplication::translate("AboutDialog", "OK", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ExitAction->setToolTip(QApplication::translate("AboutDialog", "OK", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
