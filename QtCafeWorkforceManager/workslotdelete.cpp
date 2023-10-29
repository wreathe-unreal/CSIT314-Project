#include "workslotdelete.h"
#include "ui_workslotdelete.h"
#include "QApplicationGlobal.h"
#include "popupalert.h"

void ReloadSlots(Ui::WorkSlotDelete* ui)
{
    //get user pending bids and add to bid table
    Response<QVector<Bid>> pendingBidsResponse = GetPendingBidsController().Execute();

    if(pendingBidsResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        ui->workslottable->setSortingEnabled(false);
        ui->workslottable->setRowCount(0);

        for (int i = 0; i < pendingBidsResponse.Data.size(); i ++)
        {
            if(pendingBidsResponse.Data[i].UserID == QApplicationGlobal::CurrentUserID)
            {
                ui->workslottable->setSortingEnabled(false);
                int row = ui->workslottable->rowCount();
                ui->workslottable->insertRow(row); // Insert a new row

                Response<Slot> bidSlotResponse = GetSlotController(pendingBidsResponse.Data[i].SlotID).Execute();

                if(bidSlotResponse.Result == EDatabaseResult::EDR_FAILURE)
                {
//                    QMessageBox errorMsgBox;
//                    errorMsgBox.setWindowTitle("Slot Error"); // Set the window title
//                    errorMsgBox.setText("Could not build slot!"); // Set the text to display
//                    errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
//                    errorMsgBox.exec();
                    PopupAlert popup;
                    popup.setModal(true);
                    popup.bidError();
                    popup.exec();
                    continue;
                }


                Slot bidSlot = bidSlotResponse.Data;

                // Create a new item for each piece of data/*
                QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(bidSlot.getSlotID()));
                QTableWidgetItem *date = new QTableWidgetItem(bidSlot.getDate().toString());
                QTableWidgetItem *startTime = new QTableWidgetItem(bidSlot.getStartTime().toString("hh:mm:ss AP"));
                QTableWidgetItem *endTime = new QTableWidgetItem(bidSlot.getEndTime().toString("hh:mm:ss AP"));

                // Add those items to the table
                ui->workslottable->setItem(row, 0, slotID);
                ui->workslottable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
                ui->workslottable->setItem(row, 2, startTime);  //3 is the column number for profile
                ui->workslottable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
                ui->workslottable->setSortingEnabled(true);

            }
        }
        ui->workslottable->setSortingEnabled(true);
    }
}

WorkSlotDelete::WorkSlotDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkSlotDelete)
{
    ui->setupUi(this);

    ui->workslottable->setSortingEnabled(true);
    ui->workslottable->setColumnCount(4);
    ui->workslottable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->workslottable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ReloadSlots(ui);
}

WorkSlotDelete::~WorkSlotDelete()
{
    delete ui;
}

void WorkSlotDelete::on_deleteBid_clicked()
{
    PopupAlert popup;
    popup.setModal(true);

    Response<QVector<Bid>> pendingBids = GetPendingBidsController().Execute();

    Response<void> deleteResponse;
    for (int i = 0; i < rows.size(); i++)
    {
        int row = rows[i];
        for(auto bid : pendingBids.Data)
        {
            if(bid.SlotID == ui->workslottable->item(row, 0)->text().toInt() && bid.UserID == QApplicationGlobal::CurrentUserID)
            {
                deleteResponse = DeleteBidController(bid.BidID).Execute();
            }
        }

        if(deleteResponse.Result == EDatabaseResult::EDR_FAILURE)
        {
            //        QMessageBox successMsgBox;
            //        successMsgBox.setWindowTitle("Success!"); // Set the window title
            //        successMsgBox.setText("Slot has been deleted."); // Set the text to display
            //        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

            // Show the message box as a modal dialog
            //        successMsgBox.exec();
            popup.bidDelFail();
            popup.exec();
            this->close();
        }
    }
//    QMessageBox errorMsgBox;
//    errorMsgBox.setWindowTitle("Error!"); // Set the window title
//    errorMsgBox.setText("The slot could not be deleted."); // Set the text to display
//    errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
    popup.bidDelete();
    popup.exec();
    this->close();

//    // Show the message box as a modal dialog
//    errorMsgBox.exec();
}

void WorkSlotDelete::on_workslottable_clicked(const QModelIndex &index)
{
    // Check if the index is valid
    if (!index.isValid())
    {
        ui->deleteBid->setEnabled(false);
        return;
    }

    ui->deleteBid->setEnabled(true);
    int thisrow = index.row();
    if (std::find(rows.begin(), rows.end(), thisrow) != rows.end())
        rows.erase(std::remove(rows.begin(), rows.end(), thisrow), rows.end());
    else
        rows.push_back(thisrow);
}
