#include "SysAdminWindow.h"
#include "QApplicationGlobal.h"
#include "ui_SysAdminWindow.h"
#include "AuthWindow.h"

#include <QMessageBox>

SysAdminWindow::SysAdminWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::SysAdminWindow)
{
    ui->setupUi(this);


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

    ui->userTable->setSortingEnabled(true);
    ui->userTable->setColumnCount(7);
    ui->userTable->columnWidth(450);
    ui->userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Get the horizontal header of the table widget
    QHeaderView* horizontalHeader = ui->userTable->horizontalHeader();

    // Set the stretchLastSection property
    horizontalHeader->setStretchLastSection(true);

    QStringList headers;
    headers <<"FullName" << "Username" << "Password" << "UserProfile" << "StaffRole" << "MaxSlots" << "bActive";

    ui->userTable->setHorizontalHeaderLabels(headers);


    Response<QVector<User>> usersResponse = GetUsersController().Execute();

    if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        for (auto& user : usersResponse.Data)
        {
            int row = ui->userTable->rowCount();
            ui->userTable->insertRow(row); // Insert a new row

            // Create a new item for each piece of data/*
            QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
            QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
            QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
            QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
            QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
            QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
            QString bActive = user.bActive ? "true" : "false";
            QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

            // Add those items to the table
            ui->userTable->setItem(row, 0, fullNameItem); //0 is the column number for full name
            ui->userTable->setItem(row, 1, usernameItem); // 1 is the column number for the Username
            ui->userTable->setItem(row, 2, passwordItem); // 2 is the column number for the HashedPassword
            ui->userTable->setItem(row, 3, profileItem);  //3 is the column number for profile
            ui->userTable->setItem(row, 4, roleItem); // 4 is the column number for the Role etc
            ui->userTable->setItem(row, 5, maxSlotsItem);
            ui->userTable->setItem(row, 6, bActiveItem);
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

         ui->tabWidget->setCurrentIndex(0);

        //since we must lookup the database by the old username we store it on the window's class every time the table is clicked
        UsernameBeforeEdit = ui->userTable->item(row, 1)->text();

        // Retrieve the items from the table
        QTableWidgetItem *fullNameItem = ui->userTable->item(row, 0);
        QTableWidgetItem *usernameItem = ui->userTable->item(row, 1);
        QTableWidgetItem *passwordItem = ui->userTable->item(row, 2);
        QTableWidgetItem *profileItem = ui->userTable->item(row, 3);
        QTableWidgetItem *roleItem = ui->userTable->item(row, 4);
        QTableWidgetItem *maxSlotsItem = ui->userTable->item(row, 5);
        QTableWidgetItem *bActiveItem = ui->userTable->item(row, 6);

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

}


void SysAdminWindow::on_editButton_clicked()
{
    if(ui->userTable->currentRow() == -1)
    {
            QMessageBox errorMsgBox;
            errorMsgBox.setWindowTitle("Error!"); // Set the window title
            errorMsgBox.setText("No user selected!"); // Set the text to display
            errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

            // Show the message box as a modal dialog
            errorMsgBox.exec();
            return;
    }

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
            user.setESR(ui->roleCombo->currentIndex() + 1);
    }

    Response<void> updateResponse = UpdateUserController(user, UsernameBeforeEdit).Execute();

    if(updateResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        QMessageBox successMsgBox;
        successMsgBox.setWindowTitle("Success!"); // Set the window title
        successMsgBox.setText("User has been updated."); // Set the text to display
        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

        // Show the message box as a modal dialog
        successMsgBox.exec();
    }
    else
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("The user could not be updated."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
    }


    Response<QVector<User>> usersResponse = GetUsersController().Execute();

    if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        ui->userTable->setRowCount(0);

        for (auto& user : usersResponse.Data)
        {
                int row = ui->userTable->rowCount();
                ui->userTable->insertRow(row); // Insert a new row

                // Create a new item for each piece of data/*
                QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                QString bActive = user.bActive ? "true" : "false";
                QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                // Add those items to the table
                ui->userTable->setItem(row, 0, fullNameItem);
                ui->userTable->setItem(row, 1, usernameItem); // 1 is the column number for the Username
                ui->userTable->setItem(row, 2, passwordItem); // 2 is the column number for the HashedPassword
                ui->userTable->setItem(row, 3, profileItem);  //3 is the column number for profile
                ui->userTable->setItem(row, 4, roleItem); // 4 is the column number for the Role etc
                ui->userTable->setItem(row, 5, maxSlotsItem);
                ui->userTable->setItem(row, 6, bActiveItem);
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

    Response<void> createResponse = CreateUserController(user).Execute();
    if(createResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        QMessageBox successMsgBox;
        successMsgBox.setWindowTitle("Success!"); // Set the window title
        successMsgBox.setText("User has been created."); // Set the text to display
        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

        // Show the message box as a modal dialog
        successMsgBox.exec();

        Response<QVector<User>> usersResponse = GetUsersController().Execute();

        if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
                ui->userTable->setRowCount(0);

                for (auto& user : usersResponse.Data)
                {
                    int row = ui->userTable->rowCount();
                    ui->userTable->insertRow(row); // Insert a new row

                    // Create a new item for each piece of data/*
                    QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                    QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                    QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                    QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                    QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                    QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                    QString bActive = user.bActive ? "true" : "false";
                    QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                    // Add those items to the table
                    ui->userTable->setItem(row, 0, fullNameItem);
                    ui->userTable->setItem(row, 1, usernameItem); // 1 is the column number for the Username
                    ui->userTable->setItem(row, 2, passwordItem); // 2 is the column number for the HashedPassword
                    ui->userTable->setItem(row, 3, profileItem);  //3 is the column number for profile
                    ui->userTable->setItem(row, 4, roleItem); // 4 is the column number for the Role etc
                    ui->userTable->setItem(row, 5, maxSlotsItem);
                    ui->userTable->setItem(row, 6, bActiveItem);
                }
        }
    }
    else
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("The user could not be created."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
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
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("No user selected!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
        return;
    }

    // Display the confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Confirmation", "Are you sure you want to delete?",
                                  QMessageBox::Yes|QMessageBox::No);

    // Check which button was clicked
    if (reply == QMessageBox::Yes)
    {
        QString UsernameToDelete = ui->userTable->item(ui->userTable->currentRow(), 1)->text();

        Response<void> deleteResponse = DeleteUserController(UsernameToDelete).Execute();

        if(deleteResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
            QMessageBox successMsgBox;
            successMsgBox.setWindowTitle("Success!"); // Set the window title
            successMsgBox.setText("User has been deleted."); // Set the text to display
            successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

            // Show the message box as a modal dialog
            successMsgBox.exec();

            Response<QVector<User>> usersResponse = GetUsersController().Execute();

            if(usersResponse.Result == EDatabaseResult::EDR_SUCCESS)
            {
                    ui->userTable->setRowCount(0);

                    for (auto& user : usersResponse.Data)
                    {
                        int row = ui->userTable->rowCount();
                        ui->userTable->insertRow(row); // Insert a new row

                        // Create a new item for each piece of data/*
                        QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                        QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                        QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                        QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                        QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                        QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                        QString bActive = user.bActive ? "true" : "false";
                        QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                        // Add those items to the table
                        ui->userTable->setItem(row, 0, fullNameItem);
                        ui->userTable->setItem(row, 1, usernameItem); // 1 is the column number for the Username
                        ui->userTable->setItem(row, 2, passwordItem); // 2 is the column number for the HashedPassword
                        ui->userTable->setItem(row, 3, profileItem);  //3 is the column number for profile
                        ui->userTable->setItem(row, 4, roleItem); // 4 is the column number for the Role etc
                        ui->userTable->setItem(row, 5, maxSlotsItem);
                        ui->userTable->setItem(row, 6, bActiveItem);
                    }
            }
        }
        else
        {
            QMessageBox errorMsgBox;
            errorMsgBox.setWindowTitle("Error!"); // Set the window title
            errorMsgBox.setText("The user could not be deleted."); // Set the text to display
            errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

            // Show the message box as a modal dialog
            errorMsgBox.exec();
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
    Response<QVector<User>> eupSearch = SearchByEUPController(IntToEUserProfile(ui->searchCombo->currentIndex())).Execute();

    if(eupSearch.Result == EDatabaseResult::EDR_SUCCESS && eupSearch.Data.size() > 0)
    {
        ui->userTable->setRowCount(0);

        for (auto& user : eupSearch.Data)
        {
                int row = ui->userTable->rowCount();
                ui->userTable->insertRow(row); // Insert a new row

                // Create a new item for each piece of data/*
                QTableWidgetItem *fullNameItem = new QTableWidgetItem(user.FullName);
                QTableWidgetItem *usernameItem = new QTableWidgetItem(user.Username);
                QTableWidgetItem *passwordItem = new QTableWidgetItem(user.Password);
                QTableWidgetItem *profileItem = new QTableWidgetItem(EUserProfileToQString(static_cast<EUserProfile>(user.EUP)));
                QTableWidgetItem *roleItem = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(user.ESR)));
                QTableWidgetItem *maxSlotsItem = new QTableWidgetItem(QString::number(user.MaxSlots));
                QString bActive = user.bActive ? "true" : "false";
                QTableWidgetItem *bActiveItem = new QTableWidgetItem(bActive);

                // Add those items to the table
                ui->userTable->setItem(row, 0, fullNameItem);
                ui->userTable->setItem(row, 1, usernameItem); // 1 is the column number for the Username
                ui->userTable->setItem(row, 2, passwordItem); // 2 is the column number for the HashedPassword
                ui->userTable->setItem(row, 3, profileItem);  //3 is the column number for profile
                ui->userTable->setItem(row, 4, roleItem); // 4 is the column number for the Role etc
                ui->userTable->setItem(row, 5, maxSlotsItem);
                ui->userTable->setItem(row, 6, bActiveItem);
        }
    }
    else
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("No users with specified User Profile."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
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

