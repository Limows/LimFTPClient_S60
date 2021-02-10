/********************************************************************************
** Form generated from reading UI file 'paramsdialog.ui'
**
** Created: Wed 10. Feb 23:16:29 2021
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMSDIALOG_H
#define UI_PARAMSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamsDialog
{
public:
    QAction *ExitAction;
    QTabWidget *tabWidget;
    QWidget *DownloadTabPage;
    QWidget *InstallTabPage;
    QWidget *BufferTabPage;

    void setupUi(QDialog *ParamsDialog)
    {
        if (ParamsDialog->objectName().isEmpty())
            ParamsDialog->setObjectName(QString::fromUtf8("ParamsDialog"));
        ParamsDialog->resize(240, 270);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ParamsDialog->setWindowIcon(icon);
        ExitAction = new QAction(ParamsDialog);
        ExitAction->setObjectName(QString::fromUtf8("ExitAction"));
        ExitAction->setEnabled(true);
        tabWidget = new QTabWidget(ParamsDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 240, 241));
        tabWidget->setTabPosition(QTabWidget::South);
        DownloadTabPage = new QWidget();
        DownloadTabPage->setObjectName(QString::fromUtf8("DownloadTabPage"));
        tabWidget->addTab(DownloadTabPage, QString());
        InstallTabPage = new QWidget();
        InstallTabPage->setObjectName(QString::fromUtf8("InstallTabPage"));
        tabWidget->addTab(InstallTabPage, QString());
        BufferTabPage = new QWidget();
        BufferTabPage->setObjectName(QString::fromUtf8("BufferTabPage"));
        tabWidget->addTab(BufferTabPage, QString());

        retranslateUi(ParamsDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ParamsDialog);
    } // setupUi

    void retranslateUi(QDialog *ParamsDialog)
    {
        ParamsDialog->setWindowTitle(QApplication::translate("ParamsDialog", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0, QApplication::UnicodeUTF8));
        ExitAction->setText(QApplication::translate("ParamsDialog", "Exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ExitAction->setToolTip(QApplication::translate("ParamsDialog", "Exit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(DownloadTabPage), QApplication::translate("ParamsDialog", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(InstallTabPage), QApplication::translate("ParamsDialog", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(BufferTabPage), QApplication::translate("ParamsDialog", "\320\245\321\200\320\260\320\275\320\270\320\273\320\270\321\211\320\265", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ParamsDialog: public Ui_ParamsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMSDIALOG_H
