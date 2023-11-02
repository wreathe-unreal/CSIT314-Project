#include "SysAdminWindow.h"
#include "QApplicationGlobal.h"
#include "ui_SysAdminWindow.h"
#include "AuthWindow.h"
#include "PopUp.h"

#include <QMessageBox>

SysAdminWindow::SysAdminWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::SysAdminWindow)
{
    ui->setupUi(this);
    ui->userTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->editButton->setStyleSheet("background-color: rgb(97, 255, 137); color: gainsboro;");
    ui->profileCombo->addItem("Sys Admin");
    ui->profileCombo->addItem("Cafe Owner");
    ui->profileCombo->addItem("Cafe Manager");
    ui->profileCombo->addItem("Cafe Staff");

    ui->searchCombo->addItem("Sys Admin");
    ui->searchCombo->addItem("Cafe Owner");
    ui->searchCombo->addItem("Cafe Manager");
    ui->searchCombo->addItem("Cafe Staff");

    ui->profileComboCreate->addItem("Sys Admin");
    ui->profileComboCreate->addItem("Cafe Owner");
    ui->profileComboCreate->addItem("Cafe Manager");
    ui->profileComboCreate->addItem("Cafe Staff");

    ui->roleComboCreate->setEnabled(false);
    ui->activeCheckBoxCreate->setChecked(true);

    ui->fullNameEdit->setEnabled(false);
    ui->usernameEdit->setEnabled(false);
    ui->passwordEdit->setEnabled(false);
    ui->profileCombo->setEnabled(false);
    ui->roleCombo->setEnabled(false);
    ui->activeCheckBox->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);

    ui->userTable->verticalHeader()->setVisible(false);

    ui->userTable->setSortingEnabled(true);
    ui->userTable->setColumnCount(8);
    ui->userTable->columnWidth(450);
    ui->userTable->setColumnWidth(0, 50);
    ui->userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Get the horizontal header of the table widget
    QHeaderView* horizontalHeader = ui->userTable->horizontalHeader();

    // Set the stretchLastSection property
    horizontalHeader->setStretchLastSection(true);

    QStringList headers;
    headers <<"UserID" << "Full Name" << "Username" << "Password" << "User Profile" << "Staff Role" << "Max Slots" << "Is Active?";

    ui->userTable->setHorizontalHeaderLabels(headers);


    Response<QVector<User>> usersResponse = GetUsersController::Invoke();

    if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        for (auto& user : usersResponse.Data)
        {
            int row = ui->userTable->rowCount();
            ui->userTable->insertRow(row); // Insert a new row

            // Create a new item for each piece of data/*
            QTableWidgetItem *userID = new QTableWidgetItem(QString::number(user.UserID));
            QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
            QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
            QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
            QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
            QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
            QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
            QString bActive = user.bActive ? "true" : "false";
            QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

            // Add those items to the table
            ui->userTable->setItem(row, 0, userID);
            ui->userTable->setItem(row, 1, fullNameItem);
            ui->userTable->setItem(row, 2, usernameItem);
            ui->userTable->setItem(row, 3, passwordItem);
            ui->userTable->setItem(row, 4, profileItem);
            ui->userTable->setItem(row, 5, roleItem);
            ui->userTable->setItem(row, 6, maxSlotsItem);
            ui->userTable->setItem(row, 7, bActiveItem);
        }
    }

    connect(ui->actionLogout, &QAction::triggered, this, &SysAdminWindow::OnLogoutTriggered);
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

         ui->tabWidget->setCurrentIndex(1);

        //since we must lookup the database by the old username we store it on the window's class every time the table is clicked
        UsernameBeforeEdit = ui->userTable->item(row, 2)->text();

        // Retrieve the items from the table
        QTableWidgetItem *fullNameItem = ui->userTable->item(row, 1);
        QTableWidgetItem *usernameItem = ui->userTable->item(row, 2);
        QTableWidgetItem *passwordItem = ui->userTable->item(row, 3);
        QTableWidgetItem *profileItem = ui->userTable->item(row, 4);
        QTableWidgetItem *roleItem = ui->userTable->item(row, 5);
        QTableWidgetItem *maxSlotsItem = ui->userTable->item(row, 6);
        QTableWidgetItem *bActiveItem = ui->userTable->item(row, 7);

        // Check if the items are valid
        if (!usernameItem || !passwordItem || !profileItem || !roleItem || !maxSlotsItem || !bActiveItem)
        {
            ui->fullNameEdit->setEnabled(false);
            ui->usernameEdit->setEnabled(false);
            ui->passwordEdit->setEnabled(false);
            ui->profileCombo->setEnabled(false);
            ui->roleCombo->setEnabled(false);
            ui->activeCheckBox->setEnabled(false);
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            return;
        }


        // Set the text of the QLineEdit widgets to match the text of the table items
        ui->fullNameEdit->setText(fullNameItem->text());
        ui->usernameEdit->setText(usernameItem->text());
        ui->passwordEdit->setText(passwordItem->text());
        ui->activeCheckBox->setChecked(bActiveItem->text() == "true");
        ui->profileCombo->setCurrentIndex(static_cast<int>(QStringToEUserProfile(profileItem->text())));

        //if profile is not a staff role, set role to non-staff
        if(profileItem->text() != "Cafe Staff")
        {
            ui->roleCombo->setEnabled(false);
            ui->roleCombo->clear();
            ui->roleCombo->addItem("Non-Staff");
            ui->roleCombo->setCurrentIndex(0);

        }
        else
        {
            ui->roleCombo->clear();
            ui->roleCombo->addItem("Non-Staff");
            ui->roleCombo->addItem("Chef");
            ui->roleCombo->addItem("Cashier");
            ui->roleCombo->addItem("Waiter");
            ui->roleCombo->setEnabled(false);
            ui->roleCombo->setCurrentIndex(static_cast<int>(QStringToEStaffRole(roleItem->text())));
        }

        ui->fullNameEdit->setEnabled(true);
        ui->usernameEdit->setEnabled(true);
        ui->passwordEdit->setEnabled(true);
        ui->profileCombo->setEnabled(true);
        ui->activeCheckBox->setEnabled(true);
        ui->editButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->editButton->setStyleSheet("background-color: rgb(97, 255, 137); color: dimgray;");

}


void SysAdminWindow::on_editButton_clicked()
{
    if(ui->userTable->currentRow() == -1)
    {
            PopUp error = PopUp();
            error.AdminNoUserError();
            return;
    }

    ui->createButton->setStyleSheet("background-color: rgb(97, 255, 137); color: gray;");
    User user;
    user.setFullName(ui->fullNameEdit->text());
    user.setUsername(ui->usernameEdit->text());
    user.setPassword(ui->passwordEdit->text());
    user.setbActive(ui->activeCheckBox->isChecked());
    user.setMaxSlots(ui->userTable->item(ui->userTable->currentRow(), 5)->text().toInt());
    user.setEUP(ui->profileCombo->currentIndex());

    //handle cursed staff role problems
    if(ui->profileCombo->currentIndex() != 3)
    {
            user.setESR(0);
    }
    else
    {
            user.setESR(ui->roleCombo->currentIndex());
    }

    Response<void> updateResponse = UpdateUserController::Invoke(user, UsernameBeforeEdit);

    if(updateResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
            PopUp dialogBox = PopUp();
            dialogBox.AdminUserUpdated();

    }
    else
    {
            PopUp error = PopUp();
            error.AdminUserUpdateError();
    }


    Response<QVector<User>> usersResponse = GetUsersController::Invoke();

    if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        ui->userTable->setRowCount(0);

        for (auto& user : usersResponse.Data)
        {
                int row = ui->userTable->rowCount();
                ui->userTable->insertRow(row); // Insert a new row

                // Create a new item for each piece of data/*
                QTableWidgetItem *userID = new QTableWidgetItem(QString::number(user.UserID));
                QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                QString bActive = user.bActive ? "true" : "false";
                QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                // Add those items to the table
                ui->userTable->setItem(row, 0, userID);
                ui->userTable->setItem(row, 1, fullNameItem);
                ui->userTable->setItem(row, 2, usernameItem);
                ui->userTable->setItem(row, 3, passwordItem);
                ui->userTable->setItem(row, 4, profileItem);
                ui->userTable->setItem(row, 5, roleItem);
                ui->userTable->setItem(row, 6, maxSlotsItem);
                ui->userTable->setItem(row, 7, bActiveItem);
        }
    }

    ui->fullNameEdit->clear();
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
    ui->activeCheckBox->setChecked(false);
    ui->roleCombo->setCurrentIndex(0);
    ui->profileCombo->setCurrentIndex(0);
    ui->userTable->setCurrentIndex(QModelIndex());
    ui->fullNameEdit->setEnabled(false);
    ui->usernameEdit->setEnabled(false);
    ui->passwordEdit->setEnabled(false);
    ui->activeCheckBox->setEnabled(false);
    ui->profileCombo->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->editButton->setEnabled(false);

}


void SysAdminWindow::on_createButton_clicked()
{

    User user;
    user.setFullName(ui->fullNameCreate->text());
    user.setUsername(ui->usernameCreate->text());
    user.setPassword(ui->passwordCreate->text());
    user.setbActive(ui->activeCheckBoxCreate->isChecked());
    user.setMaxSlots(0);
    user.setEUP(static_cast<int>(QStringToEUserProfile(ui->profileComboCreate->currentText())));
    user.setESR(static_cast<int>(QStringToEStaffRole(ui->roleComboCreate->currentText())));

    Response<void> createResponse = CreateUserController::Invoke(user);
    if(createResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        PopUp dialogBox = PopUp();
        dialogBox.AdminUserCreated();

        Response<QVector<User>> usersResponse = GetUsersController::Invoke();

        if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
                ui->userTable->setRowCount(0);

                for (auto& user : usersResponse.Data)
                {
                    ui->userTable->setSortingEnabled(false);
                    int row = ui->userTable->rowCount();
                    ui->userTable->insertRow(row); // Insert a new row

                    // Create a new item for each piece of data/*
                    QTableWidgetItem *userID = new QTableWidgetItem(QString::number(user.UserID));
                    QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                    QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                    QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                    QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                    QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                    QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                    QString bActive = user.bActive ? "true" : "false";
                    QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                    // Add those items to the table
                    ui->userTable->setItem(row, 0, userID);
                    ui->userTable->setItem(row, 1, fullNameItem);
                    ui->userTable->setItem(row, 2, usernameItem);
                    ui->userTable->setItem(row, 3, passwordItem);
                    ui->userTable->setItem(row, 4, profileItem);
                    ui->userTable->setItem(row, 5, roleItem);
                    ui->userTable->setItem(row, 6, maxSlotsItem);
                    ui->userTable->setItem(row, 7, bActiveItem);
                    ui->userTable->setSortingEnabled(true);
                }
        }
    }
    else
    {
        PopUp error = PopUp();
        error.AdminUserCreateError();
    }

    ui->fullNameCreate->clear();
    ui->usernameCreate->clear();
    ui->passwordCreate->clear();
    ui->activeCheckBoxCreate->setChecked(true);
    ui->roleComboCreate->setCurrentIndex(0);
    ui->profileComboCreate->setCurrentIndex(0);

}


void SysAdminWindow::on_profileCombo_currentIndexChanged(int index)
{
    if(ui->profileCombo->currentText() == "Cafe Staff")
    {
        ui->roleCombo->clear();
        ui->roleCombo->addItem("Non-Staff");
        ui->roleCombo->addItem("Chef");
        ui->roleCombo->addItem("Cashier");
        ui->roleCombo->addItem("Waiter");

    }
    else
    {
        ui->roleCombo->setEnabled(false);
        ui->roleCombo->clear();
        ui->roleCombo->addItem("Non-Staff");
        ui->roleCombo->setCurrentIndex(0);
    }

}


void SysAdminWindow::on_profileComboCreate_currentIndexChanged(int index)
{
    if(ui->profileComboCreate->currentText() == "Cafe Staff")
    {
        ui->roleComboCreate->setEnabled(true);
        ui->roleComboCreate->clear();
        ui->roleComboCreate->addItem("Non-Staff");
        ui->roleComboCreate->addItem("Chef");
        ui->roleComboCreate->addItem("Cashier");
        ui->roleComboCreate->addItem("Waiter");
    }
    else
    {
        ui->roleComboCreate->setEnabled(false);
        ui->roleComboCreate->clear();
        ui->roleComboCreate->addItem("Non-Staff");
        ui->roleComboCreate->setCurrentIndex(0);
    }
}



void SysAdminWindow::on_deleteButton_clicked()
{
    if(ui->userTable->currentRow() == -1)
    {
        PopUp error = PopUp();
        error.AdminNoUserError();
        return;
    }

    // Display the confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Confirmation", "Are you sure you want to delete?",
                                  QMessageBox::Yes|QMessageBox::No);

    // Check which button was clicked
    if (reply == QMessageBox::Yes)
    {
        int userID = ui->userTable->item(ui->userTable->currentRow(), 0)->text().toInt();


        Response<void> deleteResponse = DeleteUserController::Invoke(userID);

        if(deleteResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
            PopUp dialogBox = PopUp();
            dialogBox.AdminUserDeleted();

            Response<QVector<User>> usersResponse = GetUsersController::Invoke();

            if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
            {
                    ui->userTable->setRowCount(0);

                    for (auto& user : usersResponse.Data)
                    {
                        ui->userTable->setSortingEnabled(false);
                        int row = ui->userTable->rowCount();
                        ui->userTable->insertRow(row); // Insert a new row

                        // Create a new item for each piece of data/*
                        QTableWidgetItem *userID = new QTableWidgetItem(QString::number(user.UserID));
                        QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                        QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                        QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                        QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                        QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                        QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                        QString bActive = user.bActive ? "true" : "false";
                        QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                        // Add those items to the table
                        ui->userTable->setItem(row, 0, userID);
                        ui->userTable->setItem(row, 1, fullNameItem);
                        ui->userTable->setItem(row, 2, usernameItem);
                        ui->userTable->setItem(row, 3, passwordItem);
                        ui->userTable->setItem(row, 4, profileItem);
                        ui->userTable->setItem(row, 5, roleItem);
                        ui->userTable->setItem(row, 6, maxSlotsItem);
                        ui->userTable->setItem(row, 7, bActiveItem);
                        ui->userTable->setSortingEnabled(true);
                    }
            }
        }
        else
        {
            PopUp error = PopUp();
            error.AdminUserDeleteError();
        }
        ui->fullNameEdit->clear();
        ui->usernameEdit->clear();
        ui->passwordEdit->clear();
        ui->activeCheckBox->setChecked(false);
        ui->roleCombo->setCurrentIndex(0);
        ui->profileCombo->setCurrentIndex(0);
        ui->userTable->setCurrentIndex(QModelIndex());
        ui->fullNameEdit->setEnabled(false);
        ui->usernameEdit->setEnabled(false);
        ui->passwordEdit->setEnabled(false);
        ui->activeCheckBox->setEnabled(false);
        ui->profileCombo->setEnabled(false);
        ui->roleCombo->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->editButton->setEnabled(false);
    }
}



void SysAdminWindow::on_searchButton_clicked()
{
    Response<QVector<User>> eupSearch = SearchUsersByEUPController::Invoke(IntToEUserProfile(ui->searchCombo->currentIndex()));

    if(eupSearch.Result == EDatabaseResult::EDR_SUCCESS && eupSearch.Data.size() > 0)
    {
        ui->userTable->setRowCount(0);

        for (auto& user : eupSearch.Data)
        {
                ui->userTable->setSortingEnabled(false);
                int row = ui->userTable->rowCount();
                ui->userTable->insertRow(row); // Insert a new row

                // Create a new item for each piece of data/*
                QTableWidgetItem *userID = new QTableWidgetItem(QString::number(user.UserID));
                QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                QString bActive = user.bActive ? "true" : "false";
                QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                // Add those items to the table
                ui->userTable->setItem(row, 0, userID);
                ui->userTable->setItem(row, 1, fullNameItem);
                ui->userTable->setItem(row, 2, usernameItem);
                ui->userTable->setItem(row, 3, passwordItem);
                ui->userTable->setItem(row, 4, profileItem);
                ui->userTable->setItem(row, 5, roleItem);
                ui->userTable->setItem(row, 6, maxSlotsItem);
                ui->userTable->setItem(row, 7, bActiveItem);
                ui->userTable->setSortingEnabled(true);
        }
    }
    else
    {
        PopUp error = PopUp();
        error.AdminEUPSearchError();
    }

}

void SysAdminWindow::OnLogoutTriggered()
{
    AuthWindow* AuthView;
    AuthView = new AuthWindow;
    AuthView->setStyleSheet("AuthWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
    AuthView->show();
    this->close();
}


void SysAdminWindow::on_showAllUsersButton_clicked()
{
    Response<QVector<User>> usersResponse = GetUsersController::Invoke();

    if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        ui->userTable->setRowCount(0);

        for (auto& user : usersResponse.Data)
        {
                ui->userTable->setSortingEnabled(false);
                int row = ui->userTable->rowCount();
                ui->userTable->insertRow(row); // Insert a new row

                // Create a new item for each piece of data/*
                QTableWidgetItem *userID = new QTableWidgetItem(QString::number(user.UserID));
                QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                QString bActive = user.bActive ? "true" : "false";
                QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                // Add those items to the table
                ui->userTable->setItem(row, 0, userID);
                ui->userTable->setItem(row, 1, fullNameItem);
                ui->userTable->setItem(row, 2, usernameItem);
                ui->userTable->setItem(row, 3, passwordItem);
                ui->userTable->setItem(row, 4, profileItem);
                ui->userTable->setItem(row, 5, roleItem);
                ui->userTable->setItem(row, 6, maxSlotsItem);
                ui->userTable->setItem(row, 7, bActiveItem);
                ui->userTable->setSortingEnabled(true);
        }
    }

}

