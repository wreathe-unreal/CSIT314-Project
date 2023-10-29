/********************************************************************************
** Form generated from reading UI file 'workslotcreator.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSLOTCREATOR_H
#define UI_WORKSLOTCREATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WorkSlotCreator
{
public:
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *StartTIme;
    QTimeEdit *timestart;
    QTimeEdit *timeend;
    QLabel *EndTime;
    QPushButton *createButton;
    QPushButton *cancelCreate;
    QCalendarWidget *calendar;

    void setupUi(QDialog *WorkSlotCreator)
    {
        if (WorkSlotCreator->objectName().isEmpty())
            WorkSlotCreator->setObjectName("WorkSlotCreator");
        WorkSlotCreator->resize(343, 328);
        gridLayoutWidget_2 = new QWidget(WorkSlotCreator);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(80, 180, 178, 80));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        StartTIme = new QLabel(gridLayoutWidget_2);
        StartTIme->setObjectName("StartTIme");

        gridLayout_2->addWidget(StartTIme, 0, 0, 1, 1);

        timestart = new QTimeEdit(gridLayoutWidget_2);
        timestart->setObjectName("timestart");

        gridLayout_2->addWidget(timestart, 0, 2, 1, 1);

        timeend = new QTimeEdit(gridLayoutWidget_2);
        timeend->setObjectName("timeend");

        gridLayout_2->addWidget(timeend, 1, 2, 1, 1);

        EndTime = new QLabel(gridLayoutWidget_2);
        EndTime->setObjectName("EndTime");

        gridLayout_2->addWidget(EndTime, 1, 0, 1, 1);

        createButton = new QPushButton(WorkSlotCreator);
        createButton->setObjectName("createButton");
        createButton->setGeometry(QRect(20, 280, 80, 22));
        cancelCreate = new QPushButton(WorkSlotCreator);
        cancelCreate->setObjectName("cancelCreate");
        cancelCreate->setGeometry(QRect(240, 280, 80, 22));
        calendar = new QCalendarWidget(WorkSlotCreator);
        calendar->setObjectName("calendar");
        calendar->setGeometry(QRect(50, 20, 240, 149));

        retranslateUi(WorkSlotCreator);

        QMetaObject::connectSlotsByName(WorkSlotCreator);
    } // setupUi

    void retranslateUi(QDialog *WorkSlotCreator)
    {
        WorkSlotCreator->setWindowTitle(QCoreApplication::translate("WorkSlotCreator", "Dialog", nullptr));
        StartTIme->setText(QCoreApplication::translate("WorkSlotCreator", "Start Time:", nullptr));
        EndTime->setText(QCoreApplication::translate("WorkSlotCreator", "End Time:", nullptr));
        createButton->setText(QCoreApplication::translate("WorkSlotCreator", "Create", nullptr));
        cancelCreate->setText(QCoreApplication::translate("WorkSlotCreator", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorkSlotCreator: public Ui_WorkSlotCreator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKSLOTCREATOR_H
