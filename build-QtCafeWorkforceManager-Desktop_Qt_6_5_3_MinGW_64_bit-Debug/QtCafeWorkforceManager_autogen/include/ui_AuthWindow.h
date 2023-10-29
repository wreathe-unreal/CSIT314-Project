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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *QLE_Username;
    QLineEdit *QLE_Password;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *InvalidLoginLabel;
    QPushButton *LoginButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AuthWindow)
    {
        if (AuthWindow->objectName().isEmpty())
            AuthWindow->setObjectName("AuthWindow");
        AuthWindow->resize(763, 389);
        AuthWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(AuthWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setEnabled(true);
        groupBox->setGeometry(QRect(280, 240, 201, 101));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("Lucida Console")});
        font.setPointSize(11);
        font.setBold(true);
        font.setItalic(false);
        font.setKerning(true);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
" {\n"
"	background-color: BurlyWood ;\n"
"     border: 3px solid gray; \n"
"     border-radius: 5px; \n"
" } "));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 0, 181, 71));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        QLE_Username = new QLineEdit(layoutWidget);
        QLE_Username->setObjectName("QLE_Username");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Calibri")});
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setKerning(true);
        QLE_Username->setFont(font1);
        QLE_Username->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 46, 36);\n"
"color: rgb(202, 202, 202);\n"
"border-color: rgb(128, 128, 128);\n"
"gridline-color: rgb(128, 128, 128);"));
        QLE_Username->setFrame(true);

        verticalLayout->addWidget(QLE_Username);

        QLE_Password = new QLineEdit(layoutWidget);
        QLE_Password->setObjectName("QLE_Password");
        QLE_Password->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 46, 36);\n"
"color: rgb(202, 202, 202);\n"
"border-color: rgb(128, 128, 128);\n"
"gridline-color: rgb(128, 128, 128);"));
        QLE_Password->setFrame(true);

        verticalLayout->addWidget(QLE_Password);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 60, 181, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        InvalidLoginLabel = new QLabel(layoutWidget1);
        InvalidLoginLabel->setObjectName("InvalidLoginLabel");
        InvalidLoginLabel->setEnabled(true);
        InvalidLoginLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(InvalidLoginLabel);

        LoginButton = new QPushButton(layoutWidget1);
        LoginButton->setObjectName("LoginButton");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Calibri")});
        font2.setPointSize(10);
        font2.setBold(true);
        LoginButton->setFont(font2);
        LoginButton->setStyleSheet(QString::fromUtf8("background-color: rgb(97, 255, 137);\n"
"color:rgb(52, 52, 52)"));
        LoginButton->setAutoDefault(false);
        LoginButton->setFlat(false);

        horizontalLayout->addWidget(LoginButton);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 20, 311, 211));
        label->setPixmap(QPixmap(QString::fromUtf8(":/content/Copy of Untitled.png")));
        label->setScaledContents(true);
        AuthWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AuthWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 763, 21));
        AuthWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AuthWindow);
        statusbar->setObjectName("statusbar");
        AuthWindow->setStatusBar(statusbar);

        retranslateUi(AuthWindow);

        LoginButton->setDefault(false);


        QMetaObject::connectSlotsByName(AuthWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AuthWindow)
    {
        AuthWindow->setWindowTitle(QCoreApplication::translate("AuthWindow", "Cafe Log-in", nullptr));
        groupBox->setTitle(QString());
        QLE_Username->setText(QCoreApplication::translate("AuthWindow", "example@gmail.com", nullptr));
        QLE_Password->setText(QCoreApplication::translate("AuthWindow", "password", nullptr));
        InvalidLoginLabel->setText(QCoreApplication::translate("AuthWindow", "<html><head/><body><p><span style=\" color:#ff0004;\">Invalid Login!</span></p></body></html>", nullptr));
        LoginButton->setText(QCoreApplication::translate("AuthWindow", "Login", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AuthWindow: public Ui_AuthWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHWINDOW_H
