
#include "AuthWindow.h"
#include "./ui_AuthWindow.h"
#include <iostream>
#include "CafeStaffWindow.h"
#include <QDebug>
#include "CafeManagerWindow.h"
#include "CafeOwnerWindow.h"
#include "Response.h"
#include "SysAdminWindow.h"
#include "Controller.h"
#include "User.h"



AuthWindow::AuthWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AuthWindow)
{
    ui->setupUi(this);

    ui->InvalidLoginLabel->setVisible(false);
    ui->QLE_Password->setEchoMode(QLineEdit::Password);
    ui->LoginButton->setDefault(true);
    ui->LoginButton->setAutoDefault(true);
    ui->LoginButton->setFocusPolicy(Qt::StrongFocus);

}

AuthWindow::~AuthWindow()
{
    delete ui;
}


void AuthWindow::on_LoginButton_clicked()
{
    Response<EUserProfile> authResponse = AuthorizeController(ui->QLE_Username->text(), ui->QLE_Password->text()).Execute();
    bool bUserAuthd = authResponse.Result == EDatabaseResult::EDR_SUCCESS ? true : false;
    bool bIsActive = false;

    if(bUserAuthd)
    {
        Response<User> user = GetUserController(ui->QLE_Username->text()).Execute();
        bIsActive = user.Data.bActive;
    }


    if(!bIsActive || !bUserAuthd)
    {
        QPalette palette;
        palette.setColor(QPalette::Text, QColorConstants::Red);
        ui->QLE_Password->setPalette(palette);
        ui->QLE_Username->setPalette(palette);
        ui->InvalidLoginLabel->setVisible(true);
        return;
    }

    switch(authResponse.Data)
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
            CafeOwnerView->setStyleSheet("CafeOwnerWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
            CafeOwnerView->show();
            break;
        case EUserProfile::EUP_CafeManager:
            CafeManagerWindow* CafeManagerView;
            CafeManagerView = new CafeManagerWindow;
            CafeManagerView->setStyleSheet("CafeManagerWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
            CafeManagerView->show();
            break;
        case EUserProfile::EUP_CafeStaff:
            CafeStaffWindow* CafeStaffView;
            CafeStaffView = new CafeStaffWindow;
            CafeStaffView->setStyleSheet("CafeStaffWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
            CafeStaffView->show();
            break;
        default:
            break;
    }
    this->close(); // close the main window
}

void AuthWindow::on_QLE_Username_textChanged(const QString &arg1)
{
    QPalette palette;
    palette.setColor(QPalette::Text, QColorConstants::Black);
    ui->QLE_Username->setPalette(palette);
    ui->InvalidLoginLabel->setVisible(false);
}



void AuthWindow::on_QLE_Password_textEdited(const QString &arg1)
{
    QPalette palette;
    palette.setColor(QPalette::Text, QColorConstants::Black);
    ui->QLE_Password->setPalette(palette);
    ui->InvalidLoginLabel->setVisible(false);
}

