/********************************************************************************
** Form generated from reading UI file 'popupalert.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPUPALERT_H
#define UI_POPUPALERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PopupAlert
{
public:
    QLabel *popupText;
    QPushButton *popupButton;

    void setupUi(QDialog *PopupAlert)
    {
        if (PopupAlert->objectName().isEmpty())
            PopupAlert->setObjectName("PopupAlert");
        PopupAlert->resize(400, 92);
        popupText = new QLabel(PopupAlert);
        popupText->setObjectName("popupText");
        popupText->setGeometry(QRect(10, 10, 381, 31));
        popupButton = new QPushButton(PopupAlert);
        popupButton->setObjectName("popupButton");
        popupButton->setGeometry(QRect(160, 60, 80, 22));

        retranslateUi(PopupAlert);
        QObject::connect(popupButton, &QPushButton::clicked, PopupAlert, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(PopupAlert);
    } // setupUi

    void retranslateUi(QDialog *PopupAlert)
    {
        PopupAlert->setWindowTitle(QCoreApplication::translate("PopupAlert", "Dialog", nullptr));
        popupText->setText(QCoreApplication::translate("PopupAlert", "TextLabel", nullptr));
        popupButton->setText(QCoreApplication::translate("PopupAlert", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PopupAlert: public Ui_PopupAlert {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPUPALERT_H
