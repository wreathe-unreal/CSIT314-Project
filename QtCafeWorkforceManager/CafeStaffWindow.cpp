#include "AuthWindow.h"
#include "CafeStaffWindow.h"
#include "Enums.h"
#include "PopUp.h"
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
        ui->pendingTable->setSortingEnabled(false);
        ui->pendingTable->setRowCount(0);

        for (int i = 0; i < pendingBidsResponse.Data.size(); i ++)
        {
            if(pendingBidsResponse.Data[i].UserID == QApplicationGlobal::CurrentUserID)
            {
                ui->pendingTable->setSortingEnabled(false);
                int row = ui->pendingTable->rowCount();
                ui->pendingTable->insertRow(row); // Insert a new row

                Response<Slot> bidSlotResponse = GetSlotController(pendingBidsResponse.Data[i].SlotID).Execute();

                if(bidSlotResponse.Result == EDatabaseResult::EDR_FAILURE)
                {
                    PopUp error;
                    error.StaffSlotBuildError();
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
                ui->pendingTable->setSortingEnabled(true);

            }
        }
        ui->pendingTable->setSortingEnabled(true);
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
    ui->availableTable->setSortingEnabled(false);
    for (auto& slot : availableSlots)
    {
        ui->availableTable->setSortingEnabled(false);
        int row = ui->availableTable->rowCount();
        ui->availableTable->insertRow(row); // Insert a new row

        // Create a new item for each piece of data/*
        QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
        QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
        QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
        QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

        // Add those items to the table
        ui->availableTable->setItem(row, 0, slotID);
        ui->availableTable->setItem(row, 1, date);
        ui->availableTable->setItem(row, 2, startTime);
        ui->availableTable->setItem(row, 3, endTime);
        ui->availableTable->setSortingEnabled(true);

    }
    ui->availableTable->setSortingEnabled(true);
}


CafeStaffWindow::CafeStaffWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::CafeStaffWindow)
{
    User user = GetUserController(QApplicationGlobal::CurrentUserID).Execute().Data;
    Bid newBid;

    ui->setupUi(this);

    ui->maxSlotsBox->setValue(user.MaxSlots);
    ui->workslotText->setEnabled(false);
    connect(ui->actionLogout, &QAction::triggered, this, &CafeStaffWindow::OnLogoutTriggered);

    ui->assignedTable->verticalHeader()->setVisible(false);
    ui->assignedTable->setSortingEnabled(true);
    ui->assignedTable->setColumnCount(4);
    ui->assignedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->assignedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->assignedTable->setSelectionMode(QAbstractItemView::NoSelection);


    ui->availableTable->verticalHeader()->setVisible(false);
    ui->availableTable->setSortingEnabled(true);
    ui->availableTable->setColumnCount(4);
    ui->availableTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->availableTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->availableTable->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->pendingTable->verticalHeader()->setVisible(false);
    ui->pendingTable->setSortingEnabled(true);
    ui->pendingTable->setColumnCount(4);
    ui->pendingTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pendingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pendingTable->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->rejectedTable->verticalHeader()->setVisible(false);
    ui->rejectedTable->setSortingEnabled(true);
    ui->rejectedTable->setColumnCount(4);
    ui->rejectedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->rejectedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rejectedTable->setSelectionMode(QAbstractItemView::NoSelection);


    // Get the horizontal header of the table widget
    QHeaderView* horizontalHeader = ui->assignedTable->horizontalHeader();

    // Set the stretchLastSection property
    horizontalHeader->setStretchLastSection(false);

    QStringList headers;
    headers << "Slot ID" << "Date" << "Start Time" << "End Time";



    ui->pendingTable->setHorizontalHeaderLabels(headers);
    ui->rejectedTable->setHorizontalHeaderLabels(headers);
    ui->assignedTable->setHorizontalHeaderLabels(headers);
    ui->availableTable->setHorizontalHeaderLabels(headers);
    ui->availableTable->setColumnWidth(0, 40);
    ui->assignedTable->setColumnWidth(0, 40);
    ui->rejectedTable->setColumnWidth(1, 80);
    ui->pendingTable->setColumnWidth(1, 80);
    ui->pendingTable->setColumnWidth(0,60);
    ui->rejectedTable->setColumnWidth(0, 40);

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
    ui->assignedTable->setSortingEnabled(false);
    for (auto& slot : userSlotsResponse.Data)
    {
        ui->assignedTable->setSortingEnabled(false);
        int row = ui->assignedTable->rowCount();
        ui->assignedTable->insertRow(row); // Insert a new row

        // Create a new item for each piece of data/*
        QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
        QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
        QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
        QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

        // Add those items to the table
        ui->assignedTable->setItem(row, 0, slotID);
        ui->assignedTable->setItem(row, 1, date);
        ui->assignedTable->setItem(row, 2, startTime);
        ui->assignedTable->setItem(row, 3, endTime);
        ui->assignedTable->setSortingEnabled(true);
    }
    ui->assignedTable->setSortingEnabled(true);

    Response<QVector<Bid>> rejected = GetUserRejectedBidsController(QApplicationGlobal::CurrentUserID).Execute();

    ui->rejectedTable->setSortingEnabled(false);
    for (auto& b : rejected.Data)
    {
        Response<Slot> slotResponse = GetSlotController(b.SlotID).Execute();
        Slot slot = slotResponse.Data;
        int row = ui->rejectedTable->rowCount();
        ui->rejectedTable->insertRow(row); // Insert a new row

        // Create a new item for each piece of data/*
        QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
        QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
        QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
        QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

        // Add those items to the table
        ui->rejectedTable->setItem(row, 0, slotID);
        ui->rejectedTable->setItem(row, 1, date);
        ui->rejectedTable->setItem(row, 2, startTime);
        ui->rejectedTable->setItem(row, 3, endTime);
    }
    ui->rejectedTable->setSortingEnabled(true);


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
        PopUp error;
        error.StaffInfoUpdateFail();
        return;
    }

    Response<QVector<Slot>> userSlotsResponse = SearchSlotsByUserIDController(QApplicationGlobal::CurrentUserID).Execute();

    int curSlots = userSlotsResponse.Data.size();

    QString workSlotFraction = QString::number(curSlots) + " / " + QString::number(userResponse.Data.MaxSlots);

    ui->workslotText->setText(workSlotFraction);
    ui->maxSlotsBox->setValue(userResponse.Data.MaxSlots);

    PopUp dialogBox;
    dialogBox.StaffInfoUpdated();
    return;
}


void CafeStaffWindow::on_bidButton_clicked()
{
    QModelIndexList selectedAvailableRows = ui->availableTable->selectionModel()->selectedRows();

    if(selectedAvailableRows.isEmpty())
    {
        PopUp error;
        error.StaffBidEmptyError();
        return;
    }

    bool allBidsSuccessful = true;  // Flag to check if all bids were successful

    for(const QModelIndex &index : selectedAvailableRows)
    {
        int availableRow = index.row();

        Bid newBid;
        newBid.SlotID = ui->availableTable->item(availableRow, 0)->text().toInt();
        newBid.UserID = QApplicationGlobal::CurrentUserID;
        newBid.EBS = 0; // pending EBidStatus

        if(InsertBidController(newBid).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            allBidsSuccessful = false;
            break;  // You can decide whether you want to break on the first failure or continue trying to bid for the other slots
        }
    }

    if(!allBidsSuccessful)
    {
        PopUp error;
        error.StaffBidConflictError();
    }
    else
    {
        PopUp dialogBox;
        dialogBox.StaffBidSubmitted();
        ui->bidButton->setEnabled(false);
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
    ui->bidButton->setStyleSheet("background-color:  rgb(97, 255, 137); color: black;");
}


void CafeStaffWindow::on_pendingTable_clicked(const QModelIndex &index)
{
    // Check if the index is valid
    if (!index.isValid())
    {
        return;
    }

    ui->deleteButton->setEnabled(true);
    ui->deleteButton->setStyleSheet("background-color:rgb(235, 69, 69); color:white;");
}



void CafeStaffWindow::on_deleteButton_clicked()
{
    Response<QVector<Bid>> pendingBids = GetPendingBidsController().Execute();

    Response<void> deleteResponse;
    QModelIndexList selectedRows = ui->pendingTable->selectionModel()->selectedRows();

    for (const QModelIndex &index : selectedRows)
    {
        int row = index.row();
        for (auto bid : pendingBids.Data)
        {
            if (bid.SlotID == ui->pendingTable->item(row, 0)->text().toInt() && bid.UserID == QApplicationGlobal::CurrentUserID)
            {
                deleteResponse = DeleteBidController(bid.BidID).Execute();

                if (deleteResponse.Result != EDatabaseResult::EDR_SUCCESS)
                {
                    // Handle failure for this specific bid, perhaps log it
                }
            }
        }
    }

    // Depending on how you want to notify the user, you can adjust the following
    // For example, you can notify after every delete or only once after all deletions.
    // I'm showing a message only once after all deletions.

    if (deleteResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        PopUp dialogBox;
        dialogBox.StaffBidDeleted();

        ui->deleteButton->setEnabled(false);
        ui->deleteButton->setStyleSheet("background-color:rgb(235, 69, 69); color:gray;");

        ReloadSlots(ui);
        return;
    }
    else
    {
        PopUp error;
        error.StaffBidDeleteError();
    }
}


void CafeStaffWindow::on_workslotCalendar_clicked(const QDate &date)
{

    Response<QVector<Slot>> searchResponse = SearchSlotByDayController(ui->workslotCalendar->selectedDate()).Execute();

    if(searchResponse.Data.size() <= 0)
    {
        PopUp error;
        error.StaffSearchEmptyError();
    }
    if(searchResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error;
        error.StaffSearchError();
    }

    if(searchResponse.Result == EDatabaseResult::EDR_SUCCESS && searchResponse.Data.size() > 0)
    {
        ui->availableTable->setRowCount(0);
        ui->availableTable->setSortingEnabled(false);

        bool bSlotAvailable = true;

        qDebug() << searchResponse.Data.size();

        for (auto& slot : searchResponse.Data)
        {
            Response<QVector<User>> bidders = GetBiddersBySlotIDController(slot.SlotID).Execute();

            qDebug() << bidders.Data.size();

            for(auto& b : bidders.Data)
            {
                qDebug() << b.UserID << " " << QApplicationGlobal::CurrentUserID;
                if(b.UserID == QApplicationGlobal::CurrentUserID)
                {
                    bSlotAvailable = false;
                    qDebug() << "Slot unavailable";
                }
            }

            if(!bSlotAvailable)
            {
                continue;
            }

            ui->availableTable->setSortingEnabled(false);
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
            ui->availableTable->setSortingEnabled(true);

        }
        ui->availableTable->setSortingEnabled(true);
        if(ui->availableTable->rowCount() > 0)
        {
            PopUp dialogBox;
            dialogBox.StaffSlotSearchResult(QString::number(ui->availableTable->rowCount()));

        }
        else
        {
            QMessageBox successMsgBox;
            successMsgBox.setWindowTitle("No unbidded slots!"); // Set the window title
            successMsgBox.setText("Slots were found, but none are available for bidding by you."); // Set the text to display
            successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

            // Show the message box as a modal dialog
            successMsgBox.exec();
        }
    }
}


void CafeStaffWindow::on_pushButton_clicked()
{
    ReloadSlots(ui);
}


void CafeStaffWindow::on_updateButton_clicked()
{
    QModelIndexList selectedAvailableRows = ui->availableTable->selectionModel()->selectedRows();
    QModelIndexList selectedPendingRows = ui->pendingTable->selectionModel()->selectedRows();

    if(selectedAvailableRows.count() != 1)
    {
        PopUp dialogBox;
        dialogBox.StaffUpdateBidSelectionError();
        return;
    }

    if(selectedPendingRows.count() != 1)
    {
        PopUp dialogBox;
        dialogBox.StaffUpdateBidEmptyError();
        return;
    }

    if(ui->availableTable->currentRow() == -1 || ui->availableTable->selectedItems().isEmpty())
    {
        PopUp dialogBox;
        dialogBox.StaffUpdateBidEmptyError();
        QMessageBox errorMsgBox;
        return;
    }

    if(ui->pendingTable->currentRow() == -1 || ui->pendingTable->selectedItems().isEmpty())
    {
        PopUp dialogBox;
        dialogBox.StaffUpdateBidSelectionError();
        return;
    }


    Bid newBid;
    int availableRow = ui->availableTable->currentIndex().row();
    newBid.SlotID = ui->availableTable->item(availableRow, 0)->text().toInt();
    newBid.UserID = QApplicationGlobal::CurrentUserID;
    newBid.EBS = 0; // pending EBidStatus

    if(InsertBidController(newBid).Execute().Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp dialogBox;
        dialogBox.StaffBidConflictError();
        return;
        ui->bidButton->setEnabled(false);
        return;
    }

    int pendingRow = ui->pendingTable->currentRow();
    int pendingSlotID = ui->pendingTable->item(pendingRow, 0)->text().toInt();
    Response<QVector<Bid>> bidSlotResponse = SearchBidsBySlotIDController(pendingSlotID).Execute();


    Response<void> deleteResponse;
    for(auto& b : bidSlotResponse.Data)
    {
        if(b.UserID == QApplicationGlobal::CurrentUserID)
        {
            deleteResponse = DeleteBidController(b.BidID).Execute();

        }
    }

    if(deleteResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error = PopUp();
        error.StaffDeleteDuringUpdateError();
        error.exec();
    }

    PopUp dialogBox;
    dialogBox.StaffBidSubmitted();
    ui->bidButton->setEnabled(false);

    ReloadSlots(ui);


}

