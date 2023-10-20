#include "SysAdminWindow.h"
#include "QApplicationGlobal.h"
#include "ui_SysAdminWindow.h"

SysAdminWindow::SysAdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SysAdminWindow)
{
    ui->setupUi(this);

    ui->roleCombo->addItem("Non-Staff");
    ui->roleCombo->addItem("Cashier");
    ui->roleCombo->addItem("Waiter");
    ui->roleCombo->addItem("Chef");

    ui->profileCombo->addItem("SysAdmin");
    ui->profileCombo->addItem("Cafe Manager");
    ui->profileCombo->addItem("Cafe Owner");
    ui->profileCombo->addItem("Cafe Staff");


    ui->userTable->setColumnCount(6);
    ui->userTable->columnWidth(450);
    ui->userTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Get the horizontal header of the table widget
    QHeaderView* horizontalHeader = ui->userTable->horizontalHeader();

    // Set the stretchLastSection property
    horizontalHeader->setStretchLastSection(true);

    QStringList headers;
    headers << "Username" << "Hashed Password" << "UserProfile" << "StaffRole" << "MaxSlots" << "bActive";

    ui->userTable->setHorizontalHeaderLabels(headers);

    QVector<User> Users = GetUsersController().Execute();
    if(QApplicationGlobal::UserDAO.Result == EDatabaseResult::EDR_SUCCESS)
    {
        for (auto& user : Users)
        {
            int row = ui->userTable->rowCount();
            ui->userTable->insertRow(row); // Insert a new row

            // Create a new item for each piece of data/*
            QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
            QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
            QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
            QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
            QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
            QString bActive = user.bActive ? "true" : "false";
            QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

            // Add those items to the table
            ui->userTable->setItem(row, 0, usernameItem); // 1 is the column number for the Username
            ui->userTable->setItem(row, 1, passwordItem); // 2 is the column number for the HashedPassword
            ui->userTable->setItem(row, 2, profileItem);  //3 is the column number for profile
            ui->userTable->setItem(row, 3, roleItem); // 4 is the column number for the Role etc
            ui->userTable->setItem(row, 4, maxSlotsItem);
            ui->userTable->setItem(row, 5, bActiveItem);
        }
    }

    QApplicationGlobal::UserDAO.Result == EDatabaseResult::EDR_UNINITIALIZED;

}

SysAdminWindow::~SysAdminWindow()
{
    delete ui;
}

void SysAdminWindow::on_userTable_clicked(const QModelIndex &index)
{
        // Check if the index is valid
        if (!index.isValid())
            return;

        // Get the selected row
        int row = index.row();

        UsernameBeforeEdit = ui->userTable->item(row, 0)->text();
        //we must store the username before edit so we can update the user in the table
        //since we must lookup the table by the old username

        // Retrieve the items from the table
        QTableWidgetItem *usernameItem = ui->userTable->item(row, 0);
        QTableWidgetItem *passwordItem = ui->userTable->item(row, 1);
        QTableWidgetItem *profileItem = ui->userTable->item(row, 2);
        QTableWidgetItem *roleItem = ui->userTable->item(row, 3);
        QTableWidgetItem *bActiveItem = ui->userTable->item(row, 5);

        // Check if the items are valid
        if (!usernameItem || !passwordItem || !profileItem || !roleItem || !bActiveItem)
            return;

        // Set the text of the QLineEdit widgets to match the text of the table items
        ui->usernameEdit->setText(usernameItem->text());
        ui->passwordEdit->setText(passwordItem->text());
        ui->activeCheckBox->setChecked(!static_cast<bool>(bActiveItem->text().toInt()));
}

