
#include "AuthWindow.h"
#include "./ui_AuthWindow.h"
#include <iostream>
#include <string>
#include "CafeStaffWindow.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "CafeManagerWindow.h"
#include "CafeOwnerWindow.h"
#include "QApplicationGlobal.h"
#include "SysAdminWindow.h"


AuthWindow::AuthWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AuthWindow)
{
    ui->setupUi(this);

    ui->InvalidLoginLabel->setVisible(false);
    ui->QLE_Password->setEchoMode(QLineEdit::Password);

}

AuthWindow::~AuthWindow()
{
    delete ui;
}


void AuthWindow::on_LoginButton_clicked()
{
    AuthorizeController AuthCtrl(ui->QLE_Username->text(), ui->QLE_Password->text());
    EUserProfile userProfile = AuthCtrl.Execute();

    if(QApplicationGlobal::UserDAO.Result == EDatabaseResult::EDR_FAILURE)
    {
        QPalette palette;
        palette.setColor(QPalette::Text, QColorConstants::Red);
        ui->QLE_Password->setPalette(palette);
        ui->QLE_Username->setPalette(palette);
        ui->InvalidLoginLabel->setVisible(true);
    }

    if(QApplicationGlobal::UserDAO.Result == EDatabaseResult::EDR_SUCCESS)
    {
        switch(userProfile)
        {
            case EUserProfile::EUP_SysAdmin:
                SysAdminWindow* SysAdminView;
                SysAdminView = new SysAdminWindow;
                SysAdminView->setStyleSheet("SysAdminWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
                SysAdminView->show();
                break;
            case EUserProfile::EUP_CafeOwner:
                CafeOwnerWindow* CafeOwnerView;
                CafeOwnerView = new CafeOwnerWindow;
                CafeOwnerView->show();
                break;
            case EUserProfile::EUP_CafeManager:
                CafeManagerWindow* CafeManagerView;
                CafeManagerView = new CafeManagerWindow;
                CafeManagerView->show();
                break;
            case EUserProfile::EUP_CafeStaff:
                CafeStaffWindow* CafeStaffView;
                CafeStaffView = new CafeStaffWindow;
                CafeStaffView->show();
                break;
            default:
                break;
        }

        QApplicationGlobal::UserDAO.Result = EDatabaseResult::EDR_UNINITIALIZED;
        this->close(); // close the main window
    }
}

void AuthWindow::on_QLE_Username_textChanged(const QString &arg1)
{
    QPalette palette;
    palette.setColor(QPalette::Text, QColorConstants::Black);
    ui->QLE_Username->setPalette(palette);
}



void AuthWindow::on_QLE_Password_textEdited(const QString &arg1)
{
    QPalette palette;
    palette.setColor(QPalette::Text, QColorConstants::Black);
    ui->QLE_Password->setPalette(palette);
}

