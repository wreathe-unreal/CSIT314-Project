
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
    QString password = ui->QLE_Password->text();
    QString username = ui->QLE_Username->text();
    bool bIsActive = false;

    if(AuthorizeController::Invoke(username, password).Result == EDatabaseResult::EDR_SUCCESS)
    {
        Response<User> user = GetUserController::Invoke(username);
        bIsActive = user.Data.bActive;
    }

    bool bUserAuthorized = AuthorizeController::GetResponse().Result == EDatabaseResult::EDR_SUCCESS ? true : false;

    if(!bIsActive || !bUserAuthorized)
    {
        QPalette palette;
        palette.setColor(QPalette::Text, QColorConstants::Red);
        ui->QLE_Password->setPalette(palette);
        ui->QLE_Username->setPalette(palette);
        ui->InvalidLoginLabel->setVisible(true);
        return;
    }

    switch(AuthorizeController::GetResponse().Data)
    {
        case EUserProfile::EUP_SysAdmin:
            SysAdminWindow* SysAdminView;
            SysAdminView = new SysAdminWindow;
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

