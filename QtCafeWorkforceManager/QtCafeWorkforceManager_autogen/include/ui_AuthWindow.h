/********************************************************************************
** Form generated from reading UI file 'AuthWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHWINDOW_H
#define UI_AUTHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLineEdit *QLE_Username;
    QLineEdit *QLE_Password;
    QPushButton *LoginButton;
    QLabel *InvalidLoginLabel;
    QLabel *label;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(552, 631);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(180, 430, 201, 101));
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setBold(true);
        font.setItalic(false);
        font.setKerning(true);
        groupBox->setFont(font);
        QLE_Username = new QLineEdit(groupBox);
        QLE_Username->setObjectName("QLE_Username");
        QLE_Username->setGeometry(QRect(10, 30, 171, 16));
        QLE_Username->setFont(font);
        QLE_Password = new QLineEdit(groupBox);
        QLE_Password->setObjectName("QLE_Password");
        QLE_Password->setGeometry(QRect(10, 50, 171, 16));
        LoginButton = new QPushButton(groupBox);
        LoginButton->setObjectName("LoginButton");
        LoginButton->setGeometry(QRect(10, 70, 80, 21));
        InvalidLoginLabel = new QLabel(groupBox);
        InvalidLoginLabel->setObjectName("InvalidLoginLabel");
        InvalidLoginLabel->setEnabled(true);
        InvalidLoginLabel->setGeometry(QRect(100, 70, 81, 16));
        InvalidLoginLabel->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 210, 311, 211));
        label->setPixmap(QPixmap(QString::fromUtf8(":/content/Copy of Untitled.png")));
        label->setScaledContents(true);
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(100, 20, 351, 171));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 552, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Enter username and password:", nullptr));
        QLE_Username->setText(QCoreApplication::translate("MainWindow", "example@gmail.com", nullptr));
        QLE_Password->setText(QCoreApplication::translate("MainWindow", "password", nullptr));
        LoginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        InvalidLoginLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ff0004;\">Invalid Login!</span></p></body></html>", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHWINDOW_H
