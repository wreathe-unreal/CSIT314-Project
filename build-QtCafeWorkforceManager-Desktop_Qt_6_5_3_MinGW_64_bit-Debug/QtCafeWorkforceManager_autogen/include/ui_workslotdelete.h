/********************************************************************************
** Form generated from reading UI file 'workslotdelete.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSLOTDELETE_H
#define UI_WORKSLOTDELETE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WorkSlotDelete
{
public:
    QTableWidget *workslottable;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *deleteBid;
    QPushButton *cancelBid;

    void setupUi(QDialog *WorkSlotDelete)
    {
        if (WorkSlotDelete->objectName().isEmpty())
            WorkSlotDelete->setObjectName("WorkSlotDelete");
        WorkSlotDelete->resize(460, 312);
        workslottable = new QTableWidget(WorkSlotDelete);
        workslottable->setObjectName("workslottable");
        workslottable->setGeometry(QRect(20, 10, 421, 241));
        horizontalLayoutWidget = new QWidget(WorkSlotDelete);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 270, 421, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        deleteBid = new QPushButton(horizontalLayoutWidget);
        deleteBid->setObjectName("deleteBid");

        horizontalLayout->addWidget(deleteBid);

        cancelBid = new QPushButton(horizontalLayoutWidget);
        cancelBid->setObjectName("cancelBid");

        horizontalLayout->addWidget(cancelBid);


        retranslateUi(WorkSlotDelete);
        QObject::connect(cancelBid, &QPushButton::clicked, WorkSlotDelete, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(WorkSlotDelete);
    } // setupUi

    void retranslateUi(QDialog *WorkSlotDelete)
    {
        WorkSlotDelete->setWindowTitle(QCoreApplication::translate("WorkSlotDelete", "Dialog", nullptr));
        deleteBid->setText(QCoreApplication::translate("WorkSlotDelete", "Delete Bid", nullptr));
        cancelBid->setText(QCoreApplication::translate("WorkSlotDelete", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorkSlotDelete: public Ui_WorkSlotDelete {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKSLOTDELETE_H
