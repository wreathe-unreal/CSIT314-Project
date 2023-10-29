/********************************************************************************
** Form generated from reading UI file 'CafeStaffWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAFESTAFFWINDOW_H
#define UI_CAFESTAFFWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CafeStaffWindow
{
public:
    QAction *actionLogout;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *assignedTable;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *workslotText;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QTableWidget *rejectedTable;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *firstNameText;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QComboBox *roleCombo;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpinBox *maxSlotsBox;
    QPushButton *editInfoButton;
    QWidget *tab_3;
    QPushButton *bidButton;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QPushButton *pushButton;
    QTableWidget *availableTable;
    QPushButton *deleteButton;
    QCalendarWidget *workslotCalendar;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *pendingTable;
    QPushButton *updateButton;
    QLabel *label_10;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CafeStaffWindow)
    {
        if (CafeStaffWindow->objectName().isEmpty())
            CafeStaffWindow->setObjectName("CafeStaffWindow");
        CafeStaffWindow->resize(1194, 551);
        actionLogout = new QAction(CafeStaffWindow);
        actionLogout->setObjectName("actionLogout");
        centralwidget = new QWidget(CafeStaffWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 240, 1161, 271));
        tab = new QWidget();
        tab->setObjectName("tab");
        assignedTable = new QTableWidget(tab);
        assignedTable->setObjectName("assignedTable");
        assignedTable->setGeometry(QRect(380, 30, 361, 201));
        assignedTable->setStyleSheet(QString::fromUtf8("border:1px solid rgb(97, 255, 137)"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(380, 10, 101, 18));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");
        label_6->setEnabled(false);

        horizontalLayout_3->addWidget(label_6);

        workslotText = new QLabel(layoutWidget);
        workslotText->setObjectName("workslotText");
        workslotText->setEnabled(false);

        horizontalLayout_3->addWidget(workslotText);

        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(790, 10, 361, 221));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");
        label_3->setEnabled(false);
        QFont font;
        font.setBold(true);
        label_3->setFont(font);

        verticalLayout_3->addWidget(label_3);

        rejectedTable = new QTableWidget(layoutWidget1);
        rejectedTable->setObjectName("rejectedTable");
        rejectedTable->setEnabled(true);
        rejectedTable->setAutoFillBackground(true);
        rejectedTable->setStyleSheet(QString::fromUtf8("border:1px solid red;"));

        verticalLayout_3->addWidget(rejectedTable);

        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(30, 20, 311, 201));
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        layoutWidget2 = new QWidget(tab_4);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(40, 10, 221, 121));
        verticalLayout_6 = new QVBoxLayout(layoutWidget2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        firstNameText = new QLineEdit(layoutWidget2);
        firstNameText->setObjectName("firstNameText");

        horizontalLayout_2->addWidget(firstNameText);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName("label_7");

        horizontalLayout_4->addWidget(label_7);

        roleCombo = new QComboBox(layoutWidget2);
        roleCombo->setObjectName("roleCombo");
        roleCombo->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(roleCombo->sizePolicy().hasHeightForWidth());
        roleCombo->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(roleCombo);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName("label_4");

        horizontalLayout_5->addWidget(label_4);

        maxSlotsBox = new QSpinBox(layoutWidget2);
        maxSlotsBox->setObjectName("maxSlotsBox");
        maxSlotsBox->setMinimum(1);

        horizontalLayout_5->addWidget(maxSlotsBox);


        verticalLayout_5->addLayout(horizontalLayout_5);


        verticalLayout_6->addLayout(verticalLayout_5);

        editInfoButton = new QPushButton(tab_4);
        editInfoButton->setObjectName("editInfoButton");
        editInfoButton->setGeometry(QRect(100, 140, 111, 24));
        editInfoButton->setStyleSheet(QString::fromUtf8("background-color: green;"));
        tabWidget_2->addTab(tab_4, QString());
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        bidButton = new QPushButton(tab_3);
        bidButton->setObjectName("bidButton");
        bidButton->setGeometry(QRect(690, 80, 91, 31));
        bidButton->setStyleSheet(QString::fromUtf8("background-color:  rgb(97, 255, 137);\n"
"color: gray;"));
        layoutWidget3 = new QWidget(tab_3);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(309, 18, 371, 209));
        verticalLayout_8 = new QVBoxLayout(layoutWidget3);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_9 = new QLabel(layoutWidget3);
        label_9->setObjectName("label_9");
        label_9->setFont(font);

        horizontalLayout_6->addWidget(label_9);

        pushButton = new QPushButton(layoutWidget3);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("background-color: dodgerblue;\n"
"color: black;"));

        horizontalLayout_6->addWidget(pushButton);


        verticalLayout_8->addLayout(horizontalLayout_6);

        availableTable = new QTableWidget(layoutWidget3);
        availableTable->setObjectName("availableTable");

        verticalLayout_8->addWidget(availableTable);

        deleteButton = new QPushButton(tab_3);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setEnabled(true);
        deleteButton->setGeometry(QRect(690, 160, 91, 31));
        deleteButton->setStyleSheet(QString::fromUtf8("background-color:rgb(235, 69, 69);\n"
"color:gray;"));
        workslotCalendar = new QCalendarWidget(tab_3);
        workslotCalendar->setObjectName("workslotCalendar");
        workslotCalendar->setGeometry(QRect(21, 18, 280, 211));
        layoutWidget4 = new QWidget(tab_3);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(790, 20, 361, 201));
        verticalLayout = new QVBoxLayout(layoutWidget4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget4);
        label->setObjectName("label");
        label->setFont(font);

        verticalLayout->addWidget(label);

        pendingTable = new QTableWidget(layoutWidget4);
        pendingTable->setObjectName("pendingTable");

        verticalLayout->addWidget(pendingTable);

        updateButton = new QPushButton(tab_3);
        updateButton->setObjectName("updateButton");
        updateButton->setGeometry(QRect(690, 120, 91, 31));
        updateButton->setStyleSheet(QString::fromUtf8("background-color: gold;\n"
"color: black;"));
        tabWidget->addTab(tab_3, QString());
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(440, 10, 341, 241));
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/content/Copy of Untitled.png")));
        label_10->setScaledContents(true);
        CafeStaffWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CafeStaffWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1194, 19));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        CafeStaffWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CafeStaffWindow);
        statusbar->setObjectName("statusbar");
        CafeStaffWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLogout);

        retranslateUi(CafeStaffWindow);

        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CafeStaffWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CafeStaffWindow)
    {
        CafeStaffWindow->setWindowTitle(QCoreApplication::translate("CafeStaffWindow", "Cafe Staff Portal", nullptr));
        actionLogout->setText(QCoreApplication::translate("CafeStaffWindow", "Logout", nullptr));
        label_6->setText(QCoreApplication::translate("CafeStaffWindow", "Workslots:", nullptr));
        workslotText->setText(QCoreApplication::translate("CafeStaffWindow", "1 / 3", nullptr));
        label_3->setText(QCoreApplication::translate("CafeStaffWindow", "Rejected Bids", nullptr));
        label_5->setText(QCoreApplication::translate("CafeStaffWindow", "Full Name:", nullptr));
        label_7->setText(QCoreApplication::translate("CafeStaffWindow", "Role: ", nullptr));
        label_4->setText(QCoreApplication::translate("CafeStaffWindow", "My maximum work slots:", nullptr));
        editInfoButton->setText(QCoreApplication::translate("CafeStaffWindow", "Apply Changes", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("CafeStaffWindow", "My Info", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("CafeStaffWindow", "My Workslots", nullptr));
        bidButton->setText(QCoreApplication::translate("CafeStaffWindow", "Submit Bid ->", nullptr));
        label_9->setText(QCoreApplication::translate("CafeStaffWindow", "Available Workslots", nullptr));
        pushButton->setText(QCoreApplication::translate("CafeStaffWindow", "Show All Workslots", nullptr));
        deleteButton->setText(QCoreApplication::translate("CafeStaffWindow", "<- Remove Bid", nullptr));
        label->setText(QCoreApplication::translate("CafeStaffWindow", "Pending Bids", nullptr));
        updateButton->setText(QCoreApplication::translate("CafeStaffWindow", "<-Update->", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("CafeStaffWindow", "Manage Bids", nullptr));
        label_10->setText(QString());
        menuFile->setTitle(QCoreApplication::translate("CafeStaffWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CafeStaffWindow: public Ui_CafeStaffWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAFESTAFFWINDOW_H
