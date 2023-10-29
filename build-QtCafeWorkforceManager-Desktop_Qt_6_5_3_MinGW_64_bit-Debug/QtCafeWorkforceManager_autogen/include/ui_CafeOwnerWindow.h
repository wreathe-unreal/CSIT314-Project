/********************************************************************************
** Form generated from reading UI file 'CafeOwnerWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAFEOWNERWINDOW_H
#define UI_CAFEOWNERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
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
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CafeOwnerWindow
{
public:
    QAction *actionLogout;
    QWidget *centralwidget;
    QLabel *label;
    QTableWidget *slotTable;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *createButton;
    QCalendarWidget *calendarCreate;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *startLabel;
    QTimeEdit *startEdit;
    QVBoxLayout *verticalLayout_3;
    QLabel *endLabel;
    QTimeEdit *endEdit;
    QWidget *tab_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *slotIDEdit;
    QCalendarWidget *calendarEdit;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QLabel *startLabel_2;
    QTimeEdit *startEditEdit;
    QVBoxLayout *verticalLayout_6;
    QLabel *endLabel_2;
    QTimeEdit *endEditEdit;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QWidget *tab_4;
    QPushButton *searchButton;
    QCalendarWidget *calendarSearch;
    QPushButton *showAllButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CafeOwnerWindow)
    {
        if (CafeOwnerWindow->objectName().isEmpty())
            CafeOwnerWindow->setObjectName("CafeOwnerWindow");
        CafeOwnerWindow->resize(857, 600);
        actionLogout = new QAction(CafeOwnerWindow);
        actionLogout->setObjectName("actionLogout");
        centralwidget = new QWidget(CafeOwnerWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(560, 40, 271, 181));
        label->setPixmap(QPixmap(QString::fromUtf8(":/content/Copy of Untitled.png")));
        label->setScaledContents(true);
        slotTable = new QTableWidget(centralwidget);
        slotTable->setObjectName("slotTable");
        slotTable->setGeometry(QRect(10, 270, 811, 261));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 10, 531, 241));
        tab = new QWidget();
        tab->setObjectName("tab");
        createButton = new QPushButton(tab);
        createButton->setObjectName("createButton");
        createButton->setGeometry(QRect(370, 160, 121, 31));
        createButton->setStyleSheet(QString::fromUtf8("background-color: green;"));
        calendarCreate = new QCalendarWidget(tab);
        calendarCreate->setObjectName("calendarCreate");
        calendarCreate->setGeometry(QRect(10, 10, 331, 191));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(390, 40, 80, 106));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        startLabel = new QLabel(layoutWidget);
        startLabel->setObjectName("startLabel");

        verticalLayout_2->addWidget(startLabel);

        startEdit = new QTimeEdit(layoutWidget);
        startEdit->setObjectName("startEdit");

        verticalLayout_2->addWidget(startEdit);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        endLabel = new QLabel(layoutWidget);
        endLabel->setObjectName("endLabel");
        endLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(endLabel);

        endEdit = new QTimeEdit(layoutWidget);
        endEdit->setObjectName("endEdit");

        verticalLayout_3->addWidget(endEdit);


        verticalLayout_4->addLayout(verticalLayout_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(390, 20, 81, 48));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        slotIDEdit = new QLineEdit(layoutWidget1);
        slotIDEdit->setObjectName("slotIDEdit");
        slotIDEdit->setEnabled(false);
        slotIDEdit->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(slotIDEdit);

        calendarEdit = new QCalendarWidget(tab_2);
        calendarEdit->setObjectName("calendarEdit");
        calendarEdit->setGeometry(QRect(9, 10, 331, 191));
        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(390, 70, 80, 106));
        verticalLayout_7 = new QVBoxLayout(layoutWidget2);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        startLabel_2 = new QLabel(layoutWidget2);
        startLabel_2->setObjectName("startLabel_2");

        verticalLayout_5->addWidget(startLabel_2);

        startEditEdit = new QTimeEdit(layoutWidget2);
        startEditEdit->setObjectName("startEditEdit");

        verticalLayout_5->addWidget(startEditEdit);


        verticalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        endLabel_2 = new QLabel(layoutWidget2);
        endLabel_2->setObjectName("endLabel_2");

        verticalLayout_6->addWidget(endLabel_2);

        endEditEdit = new QTimeEdit(layoutWidget2);
        endEditEdit->setObjectName("endEditEdit");

        verticalLayout_6->addWidget(endEditEdit);


        verticalLayout_7->addLayout(verticalLayout_6);

        layoutWidget3 = new QWidget(tab_2);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(350, 180, 168, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        editButton = new QPushButton(layoutWidget3);
        editButton->setObjectName("editButton");
        editButton->setStyleSheet(QString::fromUtf8("background-color: rgb(97, 255, 137);"));

        horizontalLayout->addWidget(editButton);

        deleteButton = new QPushButton(layoutWidget3);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8("background-color: red;"));

        horizontalLayout->addWidget(deleteButton);

        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        searchButton = new QPushButton(tab_4);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(360, 90, 131, 41));
        searchButton->setStyleSheet(QString::fromUtf8("background-color: dodgerblue;\n"
"color: black;"));
        calendarSearch = new QCalendarWidget(tab_4);
        calendarSearch->setObjectName("calendarSearch");
        calendarSearch->setGeometry(QRect(9, 10, 331, 191));
        showAllButton = new QPushButton(tab_4);
        showAllButton->setObjectName("showAllButton");
        showAllButton->setGeometry(QRect(360, 140, 131, 24));
        showAllButton->setStyleSheet(QString::fromUtf8("background-color: dodgerblue;\n"
"color: black;"));
        tabWidget->addTab(tab_4, QString());
        CafeOwnerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CafeOwnerWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 857, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        CafeOwnerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CafeOwnerWindow);
        statusbar->setObjectName("statusbar");
        CafeOwnerWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLogout);

        retranslateUi(CafeOwnerWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CafeOwnerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CafeOwnerWindow)
    {
        CafeOwnerWindow->setWindowTitle(QCoreApplication::translate("CafeOwnerWindow", "Cafe Owner Portal", nullptr));
        actionLogout->setText(QCoreApplication::translate("CafeOwnerWindow", "Logout", nullptr));
        label->setText(QString());
        createButton->setText(QCoreApplication::translate("CafeOwnerWindow", "Create Workslot", nullptr));
        startLabel->setText(QCoreApplication::translate("CafeOwnerWindow", "Start Time:", nullptr));
        endLabel->setText(QCoreApplication::translate("CafeOwnerWindow", "End Time:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("CafeOwnerWindow", "Create Workslot", nullptr));
        label_2->setText(QCoreApplication::translate("CafeOwnerWindow", "Slot ID", nullptr));
        startLabel_2->setText(QCoreApplication::translate("CafeOwnerWindow", "Start Time:", nullptr));
        endLabel_2->setText(QCoreApplication::translate("CafeOwnerWindow", "End Time:", nullptr));
        editButton->setText(QCoreApplication::translate("CafeOwnerWindow", "Update", nullptr));
        deleteButton->setText(QCoreApplication::translate("CafeOwnerWindow", "Delete", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("CafeOwnerWindow", "Edit Workslot", nullptr));
        searchButton->setText(QCoreApplication::translate("CafeOwnerWindow", "Search", nullptr));
        showAllButton->setText(QCoreApplication::translate("CafeOwnerWindow", "Show All Workslots", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("CafeOwnerWindow", "Search", nullptr));
        menuFile->setTitle(QCoreApplication::translate("CafeOwnerWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CafeOwnerWindow: public Ui_CafeOwnerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAFEOWNERWINDOW_H
