/********************************************************************************
** Form generated from reading UI file 'workslotbid.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSLOTBID_H
#define UI_WORKSLOTBID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WorkSlotBid
{
public:
    QTableWidget *workslottable;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *createBid;
    QPushButton *cancelBid;

    void setupUi(QDialog *WorkSlotBid)
    {
        if (WorkSlotBid->objectName().isEmpty())
            WorkSlotBid->setObjectName("WorkSlotBid");
        WorkSlotBid->resize(460, 312);
        workslottable = new QTableWidget(WorkSlotBid);
        workslottable->setObjectName("workslottable");
        workslottable->setGeometry(QRect(20, 20, 421, 241));
        horizontalLayoutWidget = new QWidget(WorkSlotBid);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 270, 421, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        createBid = new QPushButton(horizontalLayoutWidget);
        createBid->setObjectName("createBid");

        horizontalLayout->addWidget(createBid);

        cancelBid = new QPushButton(horizontalLayoutWidget);
        cancelBid->setObjectName("cancelBid");

        horizontalLayout->addWidget(cancelBid);


        retranslateUi(WorkSlotBid);
        QObject::connect(cancelBid, &QPushButton::clicked, WorkSlotBid, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(WorkSlotBid);
    } // setupUi

    void retranslateUi(QDialog *WorkSlotBid)
    {
        WorkSlotBid->setWindowTitle(QCoreApplication::translate("WorkSlotBid", "Dialog", nullptr));
        createBid->setText(QCoreApplication::translate("WorkSlotBid", "Bid for Slot", nullptr));
        cancelBid->setText(QCoreApplication::translate("WorkSlotBid", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorkSlotBid: public Ui_WorkSlotBid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKSLOTBID_H
