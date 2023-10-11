#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCryptographicHash>
#include <QByteArray>
#include "CSVSerializer.h"

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


    CSVSerializer CSV = CSVSerializer();
    vector<User*> Users = CSV.DeserializeUsers("/content/UserTable.csv");
    for(auto user: Users)
    {
        qInfo() << user->UserID << " | " << QString::fromStdString(user->Username) << " | " << QString::fromStdString(user->HashedPassword) << " | " << EStaffRoleToInt(user->Role);
    }

    //     Deserialize CSV -> User* //user table must put ESR after uid/username/password ->separate logic for parsing each ESR type beyond uid/username/password
    //     Retrieve vector of User* store on Main()
    //
    //
    //
    //
    //
    //     Serialize CSV from User*

    for(auto user: Users)
    {
        delete user;
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

