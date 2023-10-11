#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCryptographicHash>
#include <QByteArray>
#include <iostream>
#include <string>
#include "CSVSerializer.h"
#include <QDir>

QString HashPassword(QString password)
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    return QString(hashedPassword);
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->QLE_Password->setEchoMode(QLineEdit::Password);
    ui->tableWidget->setColumnCount(4);
    QStringList headers;
    headers << "User ID" << "Username" << "Hashed Password" << "Role";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    CSVSerializer CSV = CSVSerializer();

    vector<User*> Users = CSV.DeserializeUsers("../QtCafeWorkforceManager/UserTable.csv");

    for (const auto& user : Users)
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

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoginButton_clicked()
{
    QString username = ui->QLE_Username->text();
    QString password = ui->QLE_Password->text();
    QString hashedPassword0x = HashPassword(password);

}


void MainWindow::on_columnView_clicked(const QModelIndex &index)
{

}

