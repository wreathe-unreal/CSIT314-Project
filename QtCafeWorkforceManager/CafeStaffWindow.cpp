#include "AuthWindow.h"
#include "CafeStaffWindow.h"
#include "Enums.h"
#include "QApplicationGlobal.h"
#include "ui_CafeStaffWindow.h"

#include <QDebug>
#include <QMessageBox>


void ReloadSlots(Ui::CafeStaffWindow* ui)
{
    //get user pending bids and add to bid table
    Response<QVector<Bid>> pendingBidsResponse = GetPendingBidsController().Execute();

    if(pendingBidsResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        ui->pendingTable->setRowCount(0);

        for (int i = 0; i < pendingBidsResponse.Data.size(); i ++)
        {
            if(pendingBidsResponse.Data[i].UserID == QApplicationGlobal::CurrentUserID)
            {
                int row = ui->pendingTable->rowCount();
                ui->pendingTable->insertRow(row); // Insert a new row

                Response<Slot> bidSlotResponse = GetSlotController(pendingBidsResponse.Data[i].SlotID).Execute();

                if(bidSlotResponse.Result == EDatabaseResult::EDR_FAILURE)
                {
                    QMessageBox errorMsgBox;
                    errorMsgBox.setWindowTitle("Slot Error"); // Set the window title
                    errorMsgBox.setText("Could not build slot!"); // Set the text to display
                    errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
                    errorMsgBox.exec();
                    continue;
                }


                Slot bidSlot = bidSlotResponse.Data;

                // Create a new item for each piece of data/*
                QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(bidSlot.getSlotID()));
                QTableWidgetItem *date = new QTableWidgetItem(bidSlot.getDate().toString());
                QTableWidgetItem *startTime = new QTableWidgetItem(bidSlot.getStartTime().toString("hh:mm:ss AP"));
                QTableWidgetItem *endTime = new QTableWidgetItem(bidSlot.getEndTime().toString("hh:mm:ss AP"));

                // Add those items to the table
                ui->pendingTable->setItem(row, 0, slotID);
                ui->pendingTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
                ui->pendingTable->setItem(row, 2, startTime);  //3 is the column number for profile
                ui->pendingTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
            }
        }
    }

    Response<QVector<Slot>> slotsResponse = GetSlotsController().Execute();
    Response<QVector<Bid>> searchUserBidsResponse = SearchBidsByUserIDController(QApplicationGlobal::CurrentUserID).Execute();
    Response<QVector<Slot>> searchUserSlotsResponse = SearchSlotsByUserIDController(QApplicationGlobal::CurrentUserID).Execute();


    //available workslots are workslots for which the user has no bids or assigned workslots
    QVector<Slot> availableSlots;

    for(auto& as : slotsResponse.Data)
    {
        bool bAvailable = true;

        for(auto& us : searchUserSlotsResponse.Data)
        {
            if(as.SlotID == us.SlotID)
            {
                bAvailable = false;
                continue;
            }
        }

        for(auto& bid: searchUserBidsResponse.Data)
        {
            if(as.SlotID == bid.SlotID)
            {
                bAvailable = false;
                continue;
            }
        }

        //need to check rejected bids as well
        if(bAvailable)
        {
            availableSlots.push_back(as);
        }
    }

    ui->availableTable->setRowCount(0);

    for (auto& slot : availableSlots)
    {
        int row = ui->availableTable->rowCount();
        ui->availableTable->insertRow(row); // Insert a new row

        // Create a new item for each piece of data/*
        QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
        QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
        QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
        QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

        // Add those items to the table
        ui->availableTable->setItem(row, 0, slotID);       // 1 is the column number for the Username
        ui->availableTable->setItem(row, 1, date);         // 2 is the column number for the HashedPassword
        ui->availableTable->setItem(row, 2, startTime);   //3 is the column number for profile
        ui->availableTable->setItem(row, 3, endTime);     // 4 is the column number for the Role etc
    }
}


CafeStaffWindow::CafeStaffWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::CafeStaffWindow)
{
    User user = GetUserController(QApplicationGlobal::CurrentUserID).Execute().Data;
    Bid newBid;

    ui->setupUi(this);
    ui->maxSlotsBox->setValue(user.MaxSlots);
    ui->workslotText->setEnabled(false);
    connect(ui->actionLogout, &QAction::triggered, this, &CafeStaffWindow::OnLogoutTriggered);

    ui->assignedTable->setSortingEnabled(true);
    ui->assignedTable->setColumnCount(4);
    ui->assignedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->assignedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->availableTable->setSortingEnabled(true);
    ui->availableTable->setColumnCount(4);
    ui->availableTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->availableTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->pendingTable->setSortingEnabled(true);
    ui->pendingTable->setColumnCount(4);
    ui->pendingTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pendingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->rejectedTable->setSortingEnabled(true);
    ui->rejectedTable->setColumnCount(3);
    ui->rejectedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->rejectedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Get the horizontal header of the table widget
    QHeaderView* horizontalHeader = ui->assignedTable->horizontalHeader();

    // Set the stretchLastSection property
    horizontalHeader->setStretchLastSection(false);

    QStringList headers;
    headers << "Slot ID" << "Date" << "Start Time" << "End Time";

    QStringList headers2;
    headers2 << "Date" << "Start Time" << "End Time";


    ui->assignedTable->setHorizontalHeaderLabels(headers);
    ui->availableTable->setHorizontalHeaderLabels(headers);
    ui->availableTable->setColumnWidth(0, 40);
    ui->assignedTable->setColumnWidth(0, 40);
    ui->rejectedTable->setColumnWidth(1, 80);
    ui->pendingTable->setColumnWidth(1, 80);
    ui->pendingTable->setColumnWidth(0,60);
    ui->pendingTable->setHorizontalHeaderLabels(headers);
    ui->rejectedTable->setHorizontalHeaderLabels(headers2);

    EStaffRole esr = static_cast<EStaffRole>(user.ESR);

    //handle first login
    if(esr == EStaffRole::ESR_NonStaff)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Role Selection");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint);
        msgBox.setText("Since it is your first time logging in, please set your desired role:");

        QComboBox comboBox;
        comboBox.addItem("Chef");
        comboBox.addItem("Cashier");
        comboBox.addItem("Waiter");

        QGridLayout *layout = (QGridLayout*)msgBox.layout();
        layout->addWidget(&comboBox, 0, 3, 1, 1); // Adding comboBox at top row (row index 0)

        msgBox.exec();

        esr = static_cast<EStaffRole>(comboBox.currentIndex() + 1);
        SetESRController(QApplicationGlobal::CurrentUsername, esr).Execute();
    }

    ui->firstNameText->setText(user.FullName);
    ui->roleCombo->clear();
    ui->roleCombo->addItem("Non-Staff");
    ui->roleCombo->addItem("Chef");
    ui->roleCombo->addItem("Cashier");
    ui->roleCombo->addItem("Waiter");
    ui->roleCombo->setEnabled(false);
    ui->roleCombo->setCurrentIndex(static_cast<int>(esr));

    ui->bidButton->setEnabled(false);

    ReloadSlots(ui);

    Response<QVector<Slot>> userSlotsResponse = SearchSlotsByUserIDController(QApplicationGlobal::CurrentUserID).Execute();


    int curSlots = userSlotsResponse.Data.size();

    QString workSlotFraction = QString::number(curSlots) + " / " + QString::number(user.MaxSlots);

    ui->workslotText->setText(workSlotFraction);

    for (auto& slot : userSlotsResponse.Data)
    {
        int row = ui->assignedTable->rowCount();
        ui->assignedTable->insertRow(row); // Insert a new row

        // Create a new item for each piece of data/*
        QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
        QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
        QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
        QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

        // Add those items to the table
        ui->assignedTable->setItem(row, 0, slotID); // 1 is the column number for the Username
        ui->assignedTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
        ui->assignedTable->setItem(row, 2, startTime);  //3 is the column number for profile
        ui->assignedTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
    }
}

CafeStaffWindow::~CafeStaffWindow()
{
    delete ui;
}

void CafeStaffWindow::OnLogoutTriggered()
{
    AuthWindow* AuthView;
    AuthView = new AuthWindow;
    AuthView->setStyleSheet("AuthWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
    AuthView->show();
    this->close();
}

void CafeStaffWindow::on_editInfoButton_clicked()
{
    Response<User> userResponse = GetUserController(QApplicationGlobal::CurrentUsername).Execute();
    userResponse.Data.FullName = ui->firstNameText->text();
    userResponse.Data.MaxSlots = ui->maxSlotsBox->value();
    if(UpdateUserController(userResponse.Data, QApplicationGlobal::CurrentUsername).Execute().Result == EDatabaseResult::EDR_FAILURE)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Update Failed");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint);
        msgBox.setText("Update user information failed, invalid user.");
        msgBox.exec();
        return;
    }

    Response<QVector<Slot>> userSlotsResponse = SearchSlotsByUserIDController(QApplicationGlobal::CurrentUserID).Execute();

    int curSlots = userSlotsResponse.Data.size();

    QString workSlotFraction = QString::number(curSlots) + " / " + QString::number(userResponse.Data.MaxSlots);

    ui->workslotText->setText(workSlotFraction);
    ui->maxSlotsBox->setValue(userResponse.Data.MaxSlots);

    QMessageBox successMsgBox;
    successMsgBox.setWindowTitle("Success!"); // Set the window title
    successMsgBox.setText("Your info has been updated."); // Set the text to display
    successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

    // Show the message box as a modal dialog
    successMsgBox.exec();
    return;
}


void CafeStaffWindow::on_bidButton_clicked()
{
    Bid newBid;
    int availableRow = ui->availableTable->currentIndex().row();
    newBid.SlotID = ui->availableTable->item(availableRow, 0)->text().toInt();
    newBid.UserID = QApplicationGlobal::CurrentUserID;
    newBid.EBS = 0; // pending EBidStatus

    if(InsertBidController(newBid).Execute().Result == EDatabaseResult::EDR_FAILURE)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Conflict!"); // Set the window title
        errorMsgBox.setText("A bid for this workslot already exists!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        return;
        ui->bidButton->setEnabled(false);
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Bid Confirmed!"); // Set the window title
    msgBox.setText("Your bid has been submitted."); // Set the text to display
    msgBox.setIcon(QMessageBox::Information); // Set an icon for the message box
    msgBox.exec();
    ui->bidButton->setEnabled(false);

    Response<Slot> bidSlotResponse = GetSlotController(newBid.SlotID).Execute();
    Slot bidSlot = bidSlotResponse.Data;

    if(bidSlotResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Slot Error"); // Set the window title
        errorMsgBox.setText("Could not build slot from bid!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        return;
    }

    ReloadSlots(ui);
}


void CafeStaffWindow::on_availableTable_clicked(const QModelIndex &index)
{
    // Check if the index is valid
    if (!index.isValid())
    {
        ui->bidButton->setEnabled(false);
        return;
    }

    ui->bidButton->setEnabled(true);
}


void CafeStaffWindow::on_pendingTable_clicked(const QModelIndex &index)
{
    // Check if the index is valid
    if (!index.isValid())
    {
        return;
    }

    ui->deleteButton->setEnabled(true);
}



void CafeStaffWindow::on_deleteButton_clicked()
{
    Response<QVector<Bid>> pendingBids = GetPendingBidsController().Execute();

    Response<void> deleteResponse;
    int row = ui->pendingTable->currentIndex().row();
    for(auto bid : pendingBids.Data)
    {
        if(bid.SlotID == ui->pendingTable->item(row, 0)->text().toInt() && bid.UserID == QApplicationGlobal::CurrentUserID)
        {
            deleteResponse = DeleteBidController(bid.BidID).Execute();
        }
    }

    if(deleteResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        QMessageBox successMsgBox;
        successMsgBox.setWindowTitle("Success!"); // Set the window title
        successMsgBox.setText("Slot has been deleted."); // Set the text to display
        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

        // Show the message box as a modal dialog
        successMsgBox.exec();

        ui->deleteButton->setEnabled(false);

        ReloadSlots(ui);

        return;
    }

    QMessageBox errorMsgBox;
    errorMsgBox.setWindowTitle("Error!"); // Set the window title
    errorMsgBox.setText("The slot could not be deleted."); // Set the text to display
    errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

    // Show the message box as a modal dialog
    errorMsgBox.exec();
}


void CafeStaffWindow::on_workslotCalendar_clicked(const QDate &date)
{

    Response<QVector<Slot>> searchResponse = SearchSlotByDayController(ui->workslotCalendar->selectedDate()).Execute();

    if(searchResponse.Result == EDatabaseResult::EDR_SUCCESS && searchResponse.Data.size() > 0)
    {
        QMessageBox successMsgBox;
        successMsgBox.setWindowTitle("Success!"); // Set the window title
        successMsgBox.setText("Slot search successful: " + QString::number(searchResponse.Data.size()) + " results found."); // Set the text to display
        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

        // Show the message box as a modal dialog
        successMsgBox.exec();

        ui->availableTable->setRowCount(0);

        for (auto& slot : searchResponse.Data)
        {
            int row = ui->availableTable->rowCount();
            ui->availableTable->insertRow(row); // Insert a new row


            // Create a new item for each piece of data/*
            QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
            QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
            QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

            // Add those items to the table
            ui->availableTable->setItem(row, 0, slotID); // 1 is the column number for the Username
            ui->availableTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
            ui->availableTable->setItem(row, 2, startTime);  //3 is the column number for profile
            ui->availableTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
        }
    }
    if(searchResponse.Data.size() <= 0)
    {
        QMessageBox warning;
        warning.setWindowTitle("No Results"); // Set the window title
        warning.setText("Worklot search found no results."); // Set the text to display
        warning.setIcon(QMessageBox::Warning); // Set an icon for the message box (optional)
        warning.exec();
    }
    if(searchResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        QMessageBox warning;
        warning.setWindowTitle("Error"); // Set the window title
        warning.setText("Slot search encountered an error."); // Set the text to display
        warning.setIcon(QMessageBox::Critical); // Set an icon for the message box (optional)
        warning.exec();
    }
}


void CafeStaffWindow::on_pushButton_clicked()
{
    ReloadSlots(ui);
}

