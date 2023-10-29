/********************************************************************************
** Form generated from reading UI file 'CafeManagerWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAFEMANAGERWINDOW_H
#define UI_CAFEMANAGERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CafeManagerWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CafeManagerWindow)
    {
        if (CafeManagerWindow->objectName().isEmpty())
            CafeManagerWindow->setObjectName("CafeManagerWindow");
        CafeManagerWindow->resize(800, 600);
        centralwidget = new QWidget(CafeManagerWindow);
        centralwidget->setObjectName("centralwidget");
        CafeManagerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CafeManagerWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        CafeManagerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CafeManagerWindow);
        statusbar->setObjectName("statusbar");
        CafeManagerWindow->setStatusBar(statusbar);

        retranslateUi(CafeManagerWindow);

        QMetaObject::connectSlotsByName(CafeManagerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CafeManagerWindow)
    {
        CafeManagerWindow->setWindowTitle(QCoreApplication::translate("CafeManagerWindow", "Cafe Manager Portal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CafeManagerWindow: public Ui_CafeManagerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAFEMANAGERWINDOW_H
