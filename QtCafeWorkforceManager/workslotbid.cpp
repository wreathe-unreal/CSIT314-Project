#include "workslotbid.h"
#include "ui_workslotbid.h"
#include "QApplicationGlobal.h"
#include "popupalert.h"

void ReloadSlots(Ui::WorkSlotBid* ui)
{
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

    ui->workslottable->setRowCount(0);
    ui->workslottable->setSortingEnabled(false);
    for (auto& slot : availableSlots)
    {
        ui->workslottable->setSortingEnabled(false);
        int row = ui->workslottable->rowCount();
        ui->workslottable->insertRow(row); // Insert a new row

        // Create a new item for each piece of data/*
        QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
        QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
        QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
        QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

        // Add those items to the table
        ui->workslottable->setItem(row, 0, slotID);       // 1 is the column number for the Username
        ui->workslottable->setItem(row, 1, date);         // 2 is the column number for the HashedPassword
        ui->workslottable->setItem(row, 2, startTime);   //3 is the column number for profile
        ui->workslottable->setItem(row, 3, endTime);     // 4 is the column number for the Role etc
        ui->workslottable->setSortingEnabled(true);

    }
    ui->workslottable->setSortingEnabled(true);
}

WorkSlotBid::WorkSlotBid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkSlotBid)
{
    ui->setupUi(this);

    ui->workslottable->setSortingEnabled(true);
    ui->workslottable->setColumnCount(4);
    ui->workslottable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->workslottable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->createBid->setEnabled(false);

    ReloadSlots(ui);
}

WorkSlotBid::~WorkSlotBid()
{
    delete ui;
}

void WorkSlotBid::on_createBid_clicked()
{
    PopupAlert popup;
    popup.setModal(true);

    Bid newBid;
    for (int i = 0; i < rows.size(); i++)
    {
        int bidChoice = rows[i];
        newBid.SlotID = ui->workslottable->item(bidChoice, 0)->text().toInt();
        newBid.UserID = QApplicationGlobal::CurrentUserID;
        newBid.EBS = 0; // pending EBidStatus

        if(InsertBidController(newBid).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            //        QMessageBox errorMsgBox;
            //        errorMsgBox.setWindowTitle("Bid Conflict!"); // Set the window title
            //        errorMsgBox.setText("A bid for this workslot already exists!"); // Set the text to display
            //        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
            //        errorMsgBox.exec();
            popup.bidConflict();
            popup.exec();
            return;
        }
    }

//    QMessageBox msgBox;
//    msgBox.setWindowTitle("Bid Confirmed!"); // Set the window title
//    msgBox.setText("Your bid has been submitted."); // Set the text to display
//    msgBox.setIcon(QMessageBox::Information); // Set an icon for the message box
//    msgBox.exec();
    popup.bidConfirm();
    popup.exec();
    rows.clear();

    this->close();
}

void WorkSlotBid::on_workslottable_clicked(const QModelIndex &index)
{
    // Check if the index is valid
    if (!index.isValid())
    {
        ui->createBid->setEnabled(false);
        return;
    }

    ui->createBid->setEnabled(true);
    int thisrow = index.row();
    if (std::find(rows.begin(), rows.end(), thisrow) != rows.end())
        rows.erase(std::remove(rows.begin(), rows.end(), thisrow), rows.end());
    else
        rows.push_back(thisrow);
}

