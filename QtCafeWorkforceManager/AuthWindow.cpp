#include "AuthWindow.h"
#include "./ui_AuthWindow.h"
#include <iostream>
#include <string>
#include "CafeStaffWindow.h"
#include "Commands.h"
#include "MainWindow.h"
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

//    ui->tableWidget->setColumnCount(4);

//    QStringList headers;
//    headers << "User ID" << "Username" << "Hashed Password" << "Role";

//    ui->tableWidget->setHorizontalHeaderLabels(headers);

//    CSVSerializer::DeserializeUsers();

//    for (const auto& user : QApplicationGlobal::Users)
//    {
//        int row = ui->tableWidget->rowCount();
//        ui->tableWidget->insertRow(row); // Insert a new row

//        // Create a new item for each piece of data/*
//        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(user->UserID));
//        QTableWidgetItem *usernameItem = new QTableWidgetItem(QString::fromStdString(user->Username));
//        QTableWidgetItem *passwordItem = new QTableWidgetItem(QString::fromStdString(user->HashedPassword));
//        QTableWidgetItem *roleItem = new QTableWidgetItem(QString::number(EStaffRoleToInt(user->Role)));*/

//        // Add those items to the table
//        ui->tableWidget->setItem(row, 0, idItem); // 0 is the column number for the UserID
//        ui->tableWidget->setItem(row, 1, usernameItem); // 1 is the column number for the Username
//        ui->tableWidget->setItem(row, 2, passwordItem); // 2 is the column number for the HashedPassword
//        ui->tableWidget->setItem(row, 3, roleItem); // 3 is the column number for the Role
//    }

}

AuthWindow::~AuthWindow()
{
    delete ui;
}


void AuthWindow::on_LoginButton_clicked()
{
    Authorize* AuthCmd = new Authorize();
    AuthCmd->Username = ui->QLE_Username->text();
    AuthCmd->Password = ui->QLE_Password->text();

    //create controller - handle command - delete controller
    Response AuthResponse = QApplicationGlobal::GetController()->HandleCommand(AuthCmd);
    QApplicationGlobal::SafeDeleteController();

    if(AuthResponse.Result == ECommandResult::ECR_FAILURE)
    {
        QPalette palette;
        palette.setColor(QPalette::Text, QColorConstants::Red);
        ui->QLE_Password->setPalette(palette);
        ui->QLE_Username->setPalette(palette);
        ui->InvalidLoginLabel->setVisible(true);
    }

    if(AuthResponse.Result == ECommandResult::ECR_SUCCESS)
    {
        QJsonObject jsonObj = AuthResponse.getJsonObject();
        EUserProfile UserProfile = IntToEUserProfile(jsonObj.value("EUP").toInt());

        SysAdminWindow* SysAdminView = new SysAdminWindow;
        CafeOwnerWindow* CafeOwnerView = new CafeOwnerWindow;
        CafeManagerWindow* CafeManagerView = new CafeManagerWindow;
        CafeStaffWindow* CafeStaffView = new CafeStaffWindow;

        switch(UserProfile)
        {
            case EUserProfile::EUP_SysAdmin:
                SysAdminView->show();
                break;
            case EUserProfile::EUP_CafeOwner:
                CafeOwnerView->show();
                break;
            case EUserProfile::EUP_CafeManager:
                CafeManagerView->show();
                break;
            case EUserProfile::EUP_CafeStaff:
                CafeStaffView->show();
                break;
            default:
                break;
        }

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

