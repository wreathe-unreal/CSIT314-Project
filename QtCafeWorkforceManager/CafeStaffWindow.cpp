#include "AuthWindow.h"
#include "CafeStaffWindow.h"
#include "Enums.h"
#include "QApplicationGlobal.h"
#include "ui_CafeStaffWindow.h"

#include <QDebug>
#include <QMessageBox>


void ReloadSlots(Ui::CafeStaffWindow* ui)
{
    //get user id
    int userID = GetUserIDController(QApplicationGlobal::CurrentUsername).Execute();

    //use userid to get userslots
    QVector<Slot> userSlots = SearchSlotsByUserIDController(userID).Execute();


    //get user pending bids and add to bid table
    QVector<Bid> pendingBids = GetPendingBidsController().Execute();

    if(GetBidDAOResult().Execute() == EDatabaseResult::EDR_SUCCESS)
    {
        ui->pendingTable->setRowCount(0);

        for (auto& bid : pendingBids)
        {
            int row = ui->pendingTable->rowCount();
            ui->pendingTable->insertRow(row); // Insert a new row

            Slot bidSlot = GetSlotController(bid.SlotID).Execute();

            if(GetSlotDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
            {
                QMessageBox errorMsgBox;
                errorMsgBox.setWindowTitle("Slot Error"); // Set the window title
                errorMsgBox.setText("Could not build slot!"); // Set the text to display
                errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
                errorMsgBox.exec();
                ResetSlotDAOResult().Execute();
                continue;
            }

            // Create a new item for each piece of data/*
            QTableWidgetItem *date = new QTableWidgetItem(bidSlot.getDate().toString());
            QTableWidgetItem *startTime = new QTableWidgetItem(bidSlot.getStartTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *endTime = new QTableWidgetItem(bidSlot.getEndTime().toString("hh:mm:ss AP"));

            // Add those items to the table
            ui->pendingTable->setItem(row, 0, date); // 2 is the column number for the HashedPassword
            ui->pendingTable->setItem(row, 1, startTime);  //3 is the column number for profile
            ui->pendingTable->setItem(row, 2, endTime); // 4 is the column number for the Role etc
        }
    }

    ResetUserDAOResult().Execute();


    QVector<Slot> allSlots = GetSlotsController().Execute();

    if(GetSlotDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        ResetSlotDAOResult().Execute();
        return;
    }

    QVector<Bid> userBids = SearchBidsByUserIDController(userID).Execute();
    if(GetSlotDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        ResetSlotDAOResult().Execute();
        return;
    }


    //available workslots are workslots for which the user has no bids
    QVector<Slot> availableSlots;

    for(auto& as : allSlots)
    {
        bool bAvailable = true;

        for(auto& us : userSlots)
        {
            if(as.SlotID == us.SlotID)
            {
                bAvailable = false;
                continue;
            }
        }

        for(auto& bid: userBids)
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
    Bid newBid;

    ui->setupUi(this);
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

    ui->submittedTable->setSortingEnabled(true);
    ui->submittedTable->setColumnCount(3);
    ui->submittedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->submittedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->pendingTable->setSortingEnabled(true);
    ui->pendingTable->setColumnCount(3);
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
    ui->submittedTable->setHorizontalHeaderLabels(headers2);
    ui->pendingTable->setHorizontalHeaderLabels(headers2);
    ui->approvedTable->setHorizontalHeaderLabels(headers2);
    ui->rejectedTable->setHorizontalHeaderLabels(headers2);

    EStaffRole esr = GetESRController(QApplicationGlobal::CurrentUsername).Execute();

    if(GetUserDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Failed to find Staff Role."); // Set the window title
        msgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)
        msgBox.setText("Logging out. Please speak to Sys Admin.");
        msgBox.exec();
        OnLogoutTriggered();
    }

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

        EStaffRole newESR = static_cast<EStaffRole>(comboBox.currentIndex() + 1);
        SetESRController(QApplicationGlobal::CurrentUsername, newESR).Execute();
    }


    ui->firstNameText->setText(GetNameController(QApplicationGlobal::CurrentUsername).Execute());
    ui->roleCombo->clear();
    ui->roleCombo->addItem("Non-Staff");
    ui->roleCombo->addItem("Chef");
    ui->roleCombo->addItem("Cashier");
    ui->roleCombo->addItem("Waiter");
    ui->roleCombo->setEnabled(false);
    ui->roleCombo->setCurrentIndex(static_cast<int>(esr));

    ui->bidButton->setEnabled(false);

    ReloadSlots(ui);

    int userID = GetUserIDController(QApplicationGlobal::CurrentUsername).Execute();


    QVector<Slot> userSlots;
    if(GetUserDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        ResetUserDAOResult().Execute();
        return;
    }

    userSlots = SearchSlotsByUserIDController(userID).Execute();
    int maxSlots = GetUserController(QApplicationGlobal::CurrentUsername).Execute().MaxSlots;
    int curSlots = userSlots.size();
    QString workSlotFraction = QString::number(curSlots) + " / " + QString::number(maxSlots);

    ui->workslotText->setText(workSlotFraction);


    if(GetSlotDAOResult().Execute() == EDatabaseResult::EDR_SUCCESS)
    {
        for (auto& slot : userSlots)
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
    else if(GetSlotDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        ResetSlotDAOResult().Execute();
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
    User updatedUser = GetUserController(QApplicationGlobal::CurrentUsername).Execute();
    updatedUser.FullName = ui->firstNameText->text();
    updatedUser.MaxSlots = ui->maxSlotsBox->value();

    if(GetUserDAOResult().Execute() == EDatabaseResult::EDR_SUCCESS)
    {
        UpdateUserController(updatedUser, QApplicationGlobal::CurrentUsername).Execute();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Update Failed");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint);
        msgBox.setText("Update user information failed, invalid user.");
        msgBox.exec();
        return;
    }

    if(GetUserDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Update Failed");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowCloseButtonHint);
        msgBox.setText("Update user information failed, user not found.");
        msgBox.exec();
        return;
    }

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
    int row = ui->availableTable->currentIndex().row();
    newBid.SlotID = ui->availableTable->item(row, 0)->text().toInt();
    newBid.UserID = GetUserIDController(QApplicationGlobal::CurrentUsername).Execute();
    newBid.EBS = 0; // pending EBidStatus

    if(GetUserDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Conflict!"); // Set the window title
        errorMsgBox.setText("A bid for this workslot already exists!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        ResetUserDAOResult().Execute();
        return;
    }

    InsertBidController(newBid).Execute();

    if(GetBidDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        ui->bidButton->setEnabled(false);
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Bid Confirmed!"); // Set the window title
    msgBox.setText("Your bid has been submitted."); // Set the text to display
    msgBox.setIcon(QMessageBox::Information); // Set an icon for the message box
    msgBox.exec();
    ui->bidButton->setEnabled(false);

    int row2 = ui->submittedTable->rowCount();
    ui->submittedTable->insertRow(row2); // Insert a new row

    Slot bidSlot = GetSlotController(newBid.SlotID).Execute();

    if(GetSlotDAOResult().Execute() == EDatabaseResult::EDR_FAILURE)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Slot Error"); // Set the window title
        errorMsgBox.setText("Could not build slot from bid!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        ResetSlotDAOResult().Execute();
        return;
    }

    // Create a new item for each piece of data/*
    QTableWidgetItem *date = new QTableWidgetItem(bidSlot.getDate().toString());
    QTableWidgetItem *startTime = new QTableWidgetItem(bidSlot.getStartTime().toString("hh:mm:ss AP"));
    QTableWidgetItem *endTime = new QTableWidgetItem(bidSlot.getEndTime().toString("hh:mm:ss AP"));

    // Add those items to the table
    ui->submittedTable->setItem(row, 0, date); // 2 is the column number for the HashedPassword
    ui->submittedTable->setItem(row, 1, startTime);  //3 is the column number for profile
    ui->submittedTable->setItem(row, 2, endTime); // 4 is the column number for the Role etc

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

