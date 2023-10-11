#include "AuthWindow.h"
#include "./ui_AuthWindow.h"
#include <iostream>
#include <string>
#include "CSVSerializer.h"
#include "Commands.h"
#include "MainWindow.h"
#include "QApplicationGlobal.h"

AuthWindow::AuthWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->InvalidLoginLabel->setVisible(false);
    ui->QLE_Password->setEchoMode(QLineEdit::Password);

    ui->tableWidget->setColumnCount(4);

    QStringList headers;
    headers << "User ID" << "Username" << "Hashed Password" << "Role";

    ui->tableWidget->setHorizontalHeaderLabels(headers);

    CSVSerializer::DeserializeUsers();

    for (const auto& user : QApplicationGlobal::Users)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row); // Insert a new row

        // Create a new item for each piece of data
        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(user->UserID));
        QTableWidgetItem *usernameItem = new QTableWidgetItem(QString::fromStdString(user->Username));
        QTableWidgetItem *passwordItem = new QTableWidgetItem(QString::fromStdString(user->HashedPassword));
        QTableWidgetItem *roleItem = new QTableWidgetItem(QString::number(EStaffRoleToInt(user->Role)));

        // Add those items to the table
        ui->tableWidget->setItem(row, 0, idItem); // 0 is the column number for the UserID
        ui->tableWidget->setItem(row, 1, usernameItem); // 1 is the column number for the Username
        ui->tableWidget->setItem(row, 2, passwordItem); // 2 is the column number for the HashedPassword
        ui->tableWidget->setItem(row, 3, roleItem); // 3 is the column number for the Role
    }

}

AuthWindow::~AuthWindow()
{
    delete ui;
}


void AuthWindow::on_LoginButton_clicked()
{
    Authorize* Cmd = new Authorize();
    Cmd->Username = ui->QLE_Username->text();
    Cmd->Password = ui->QLE_Password->text();
    ECommandResult Authenticated = QApplicationGlobal::CmdController.HandleCommand(Cmd);

    if(Authenticated == ECommandResult::ECR_FAILURE)
    {
        QPalette palette;
        palette.setColor(QPalette::Text, QColorConstants::Red);
        ui->QLE_Password->setPalette(palette);
        ui->QLE_Username->setPalette(palette);
        ui->InvalidLoginLabel->setVisible(true);
    }
    if(Authenticated == ECommandResult::ECR_SUCCESS)
    {
        MainWindow* MainView = new MainWindow; // create a new second window
        MainView->show(); // show the second window
        this->close(); // close the main window
    }
}


void AuthWindow::on_columnView_clicked(const QModelIndex &index)
{

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

