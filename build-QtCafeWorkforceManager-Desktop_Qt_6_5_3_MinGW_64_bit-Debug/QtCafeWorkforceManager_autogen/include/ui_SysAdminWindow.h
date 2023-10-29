/********************************************************************************
** Form generated from reading UI file 'SysAdminWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSADMINWINDOW_H
#define UI_SYSADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SysAdminWindow
{
public:
    QAction *actionLogout;
    QWidget *centralwidget;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *usernameCreate;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLineEdit *passwordCreate;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QComboBox *profileComboCreate;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QComboBox *roleComboCreate;
    QCheckBox *activeCheckBoxCreate;
    QPushButton *createButton;
    QWidget *layoutWidget_7;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_12;
    QLineEdit *fullNameCreate;
    QWidget *tab;
    QCheckBox *activeCheckBox;
    QPushButton *editButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *usernameEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *passwordEdit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *profileCombo;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *roleCombo;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QLineEdit *fullNameEdit;
    QPushButton *deleteButton;
    QWidget *tab_4;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout;
    QPushButton *searchButton;
    QPushButton *showAllUsersButton;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_10;
    QComboBox *searchCombo;
    QTableWidget *userTable;
    QTableWidget *userTable_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SysAdminWindow)
    {
        if (SysAdminWindow->objectName().isEmpty())
            SysAdminWindow->setObjectName("SysAdminWindow");
        SysAdminWindow->resize(800, 576);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SysAdminWindow->sizePolicy().hasHeightForWidth());
        SysAdminWindow->setSizePolicy(sizePolicy);
        SysAdminWindow->setMinimumSize(QSize(800, 576));
        SysAdminWindow->setMaximumSize(QSize(800, 576));
        actionLogout = new QAction(SysAdminWindow);
        actionLogout->setObjectName("actionLogout");
        centralwidget = new QWidget(SysAdminWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(470, 40, 271, 181));
        label->setPixmap(QPixmap(QString::fromUtf8(":/content/Copy of Untitled.png")));
        label->setScaledContents(true);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 30, 401, 191));
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        layoutWidget_2 = new QWidget(tab_2);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(20, 10, 171, 26));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName("label_6");

        horizontalLayout_5->addWidget(label_6);

        usernameCreate = new QLineEdit(layoutWidget_2);
        usernameCreate->setObjectName("usernameCreate");

        horizontalLayout_5->addWidget(usernameCreate);

        layoutWidget_3 = new QWidget(tab_2);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(20, 40, 171, 26));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget_3);
        label_7->setObjectName("label_7");

        horizontalLayout_6->addWidget(label_7);

        passwordCreate = new QLineEdit(layoutWidget_3);
        passwordCreate->setObjectName("passwordCreate");

        horizontalLayout_6->addWidget(passwordCreate);

        layoutWidget_4 = new QWidget(tab_2);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(200, 10, 191, 26));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget_4);
        label_8->setObjectName("label_8");

        horizontalLayout_7->addWidget(label_8);

        profileComboCreate = new QComboBox(layoutWidget_4);
        profileComboCreate->setObjectName("profileComboCreate");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(profileComboCreate->sizePolicy().hasHeightForWidth());
        profileComboCreate->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(profileComboCreate);

        layoutWidget_5 = new QWidget(tab_2);
        layoutWidget_5->setObjectName("layoutWidget_5");
        layoutWidget_5->setGeometry(QRect(200, 40, 191, 26));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget_5);
        label_9->setObjectName("label_9");

        horizontalLayout_8->addWidget(label_9);

        roleComboCreate = new QComboBox(layoutWidget_5);
        roleComboCreate->setObjectName("roleComboCreate");
        sizePolicy1.setHeightForWidth(roleComboCreate->sizePolicy().hasHeightForWidth());
        roleComboCreate->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(roleComboCreate);

        activeCheckBoxCreate = new QCheckBox(tab_2);
        activeCheckBoxCreate->setObjectName("activeCheckBoxCreate");
        activeCheckBoxCreate->setGeometry(QRect(320, 100, 71, 22));
        activeCheckBoxCreate->setLayoutDirection(Qt::RightToLeft);
        createButton = new QPushButton(tab_2);
        createButton->setObjectName("createButton");
        createButton->setGeometry(QRect(20, 110, 121, 31));
        createButton->setStyleSheet(QString::fromUtf8("background-color: green;"));
        layoutWidget_7 = new QWidget(tab_2);
        layoutWidget_7->setObjectName("layoutWidget_7");
        layoutWidget_7->setGeometry(QRect(20, 70, 371, 26));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_7);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget_7);
        label_12->setObjectName("label_12");

        horizontalLayout_11->addWidget(label_12);

        fullNameCreate = new QLineEdit(layoutWidget_7);
        fullNameCreate->setObjectName("fullNameCreate");

        horizontalLayout_11->addWidget(fullNameCreate);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        activeCheckBox = new QCheckBox(tab);
        activeCheckBox->setObjectName("activeCheckBox");
        activeCheckBox->setEnabled(true);
        activeCheckBox->setGeometry(QRect(310, 110, 71, 22));
        activeCheckBox->setLayoutDirection(Qt::RightToLeft);
        activeCheckBox->setAutoFillBackground(false);
        activeCheckBox->setChecked(true);
        editButton = new QPushButton(tab);
        editButton->setObjectName("editButton");
        editButton->setGeometry(QRect(10, 110, 121, 31));
        editButton->setStyleSheet(QString::fromUtf8("background-color: rgb(97, 255, 137);\n"
"color: dimgray;"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 20, 191, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        usernameEdit = new QLineEdit(layoutWidget);
        usernameEdit->setObjectName("usernameEdit");

        horizontalLayout->addWidget(usernameEdit);

        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 50, 191, 26));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        passwordEdit = new QLineEdit(layoutWidget1);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEnabled(true);

        horizontalLayout_2->addWidget(passwordEdit);

        layoutWidget2 = new QWidget(tab);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(210, 20, 171, 26));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        profileCombo = new QComboBox(layoutWidget2);
        profileCombo->setObjectName("profileCombo");
        sizePolicy1.setHeightForWidth(profileCombo->sizePolicy().hasHeightForWidth());
        profileCombo->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(profileCombo);

        layoutWidget3 = new QWidget(tab);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(210, 50, 171, 26));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        roleCombo = new QComboBox(layoutWidget3);
        roleCombo->setObjectName("roleCombo");
        sizePolicy1.setHeightForWidth(roleCombo->sizePolicy().hasHeightForWidth());
        roleCombo->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(roleCombo);

        layoutWidget_6 = new QWidget(tab);
        layoutWidget_6->setObjectName("layoutWidget_6");
        layoutWidget_6->setGeometry(QRect(10, 80, 371, 26));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget_6);
        label_11->setObjectName("label_11");

        horizontalLayout_10->addWidget(label_11);

        fullNameEdit = new QLineEdit(layoutWidget_6);
        fullNameEdit->setObjectName("fullNameEdit");

        horizontalLayout_10->addWidget(fullNameEdit);

        deleteButton = new QPushButton(tab);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(140, 110, 81, 31));
        deleteButton->setStyleSheet(QString::fromUtf8("background-color: red;"));
        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        layoutWidget4 = new QWidget(tab_4);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(160, 80, 87, 56));
        verticalLayout = new QVBoxLayout(layoutWidget4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        searchButton = new QPushButton(layoutWidget4);
        searchButton->setObjectName("searchButton");
        searchButton->setStyleSheet(QString::fromUtf8("background-color: dodgerblue;\n"
"color: black;"));

        verticalLayout->addWidget(searchButton);

        showAllUsersButton = new QPushButton(layoutWidget4);
        showAllUsersButton->setObjectName("showAllUsersButton");

        verticalLayout->addWidget(showAllUsersButton);

        layoutWidget5 = new QWidget(tab_4);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(120, 30, 161, 48));
        verticalLayout_2 = new QVBoxLayout(layoutWidget5);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget5);
        label_10->setObjectName("label_10");

        verticalLayout_2->addWidget(label_10);

        searchCombo = new QComboBox(layoutWidget5);
        searchCombo->setObjectName("searchCombo");

        verticalLayout_2->addWidget(searchCombo);

        tabWidget->addTab(tab_4, QString());
        userTable = new QTableWidget(centralwidget);
        userTable->setObjectName("userTable");
        userTable->setGeometry(QRect(20, 240, 741, 291));
        userTable_2 = new QTableWidget(centralwidget);
        userTable_2->setObjectName("userTable_2");
        userTable_2->setGeometry(QRect(250, 570, 741, 261));
        SysAdminWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SysAdminWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        SysAdminWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SysAdminWindow);
        statusbar->setObjectName("statusbar");
        SysAdminWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLogout);

        retranslateUi(SysAdminWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SysAdminWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SysAdminWindow)
    {
        SysAdminWindow->setWindowTitle(QCoreApplication::translate("SysAdminWindow", "Cafe SysAdmin Portal", nullptr));
        actionLogout->setText(QCoreApplication::translate("SysAdminWindow", "Logout", nullptr));
        label->setText(QString());
        label_6->setText(QCoreApplication::translate("SysAdminWindow", "Username:", nullptr));
        usernameCreate->setText(QCoreApplication::translate("SysAdminWindow", "username", nullptr));
        label_7->setText(QCoreApplication::translate("SysAdminWindow", "Password: ", nullptr));
        passwordCreate->setText(QCoreApplication::translate("SysAdminWindow", "password", nullptr));
        label_8->setText(QCoreApplication::translate("SysAdminWindow", "User Profile:", nullptr));
        label_9->setText(QCoreApplication::translate("SysAdminWindow", "Staff Role:", nullptr));
        activeCheckBoxCreate->setText(QCoreApplication::translate("SysAdminWindow", "Is Active?", nullptr));
        createButton->setText(QCoreApplication::translate("SysAdminWindow", "Create User", nullptr));
        label_12->setText(QCoreApplication::translate("SysAdminWindow", "Full Name:", nullptr));
        fullNameCreate->setText(QCoreApplication::translate("SysAdminWindow", "John Doe", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SysAdminWindow", "Create User", nullptr));
        activeCheckBox->setText(QCoreApplication::translate("SysAdminWindow", "Is Active?", nullptr));
        editButton->setText(QCoreApplication::translate("SysAdminWindow", "Apply Changes", nullptr));
        label_2->setText(QCoreApplication::translate("SysAdminWindow", "Username:", nullptr));
        label_3->setText(QCoreApplication::translate("SysAdminWindow", "Password: ", nullptr));
        label_4->setText(QCoreApplication::translate("SysAdminWindow", "User Profile:", nullptr));
        label_5->setText(QCoreApplication::translate("SysAdminWindow", "Staff Role:", nullptr));
        label_11->setText(QCoreApplication::translate("SysAdminWindow", "Full Name:", nullptr));
        deleteButton->setText(QCoreApplication::translate("SysAdminWindow", "Delete User", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SysAdminWindow", "Edit User", nullptr));
        searchButton->setText(QCoreApplication::translate("SysAdminWindow", "Search", nullptr));
        showAllUsersButton->setText(QCoreApplication::translate("SysAdminWindow", "Show All Users", nullptr));
        label_10->setText(QCoreApplication::translate("SysAdminWindow", "Filter User Profile: ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("SysAdminWindow", "Search User", nullptr));
        menuFile->setTitle(QCoreApplication::translate("SysAdminWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SysAdminWindow: public Ui_SysAdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSADMINWINDOW_H
