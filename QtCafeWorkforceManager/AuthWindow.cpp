
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
    //attach ui pointer
    ui->setupUi(this);

    //setup the UI
    ui->InvalidLoginLabel->setVisible(false);
    ui->QLE_Password->setEchoMode(QLineEdit::Password);
    ui->LoginButton->setDefault(true);
    ui->LoginButton->setAutoDefault(true);
    ui->LoginButton->setFocusPolicy(Qt::StrongFocus);

}

//desetructor
AuthWindow::~AuthWindow()
{
    delete ui;
}


void AuthWindow::on_LoginButton_clicked()
{
    QString password = ui->QLE_Password->text();
    QString username = ui->QLE_Username->text();
    bool bIsActive = false;

    //if Authorize execution database result succceeds

    if(AuthorizeController::Invoke(username, password).Result == EDatabaseResult::EDR_SUCCESS)
    {
        Response<User> user = GetUserController::Invoke(username);
        bIsActive = user.Data.bActive; //set user active boolean
    }

    //check if user was authorized
    bool bUserAuthorized = AuthorizeController::GetResponse().Result == EDatabaseResult::EDR_SUCCESS ? true : false;

    //if either the user is not authorize or the user is not active
    //set text red and return
    if(!bIsActive || !bUserAuthorized)
    {
        QPalette palette;
        palette.setColor(QPalette::Text, QColorConstants::Red);
        ui->QLE_Password->setPalette(palette);
        ui->QLE_Username->setPalette(palette);
        ui->InvalidLoginLabel->setVisible(true);
        return;
    }

    //since the authorize controller returns the user's EUserProfile
    //we get this from the Response with GetResponse().Data and switch on it
    //to decide which window to open
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
    //set text black when the text has changed (only relevant when the text is red from a previous failure)
    QPalette palette;
    palette.setColor(QPalette::Text, QColorConstants::Black);
    ui->QLE_Username->setPalette(palette);
    ui->InvalidLoginLabel->setVisible(false);
}



void AuthWindow::on_QLE_Password_textEdited(const QString &arg1)
{
    //set text black when the text has changed (only relevant when the text is red from a previous failure)
    QPalette palette;
    palette.setColor(QPalette::Text, QColorConstants::Black);
    ui->QLE_Password->setPalette(palette);
    ui->InvalidLoginLabel->setVisible(false);
}


void AuthWindow::on_QLE_Password_returnPressed()
{
    //press login button when return is pressed from the password field's text bos
    AuthWindow::on_LoginButton_clicked();
}

