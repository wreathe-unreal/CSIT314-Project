#include "AuthWindow.h"
#include "CafeManagerWindow.h"
#include "Controller.h"
#include "Enums.h"
#include "Response.h"
#include "Slot.h"
#include "ui_CafeManagerWindow.h"

#include <QMessageBox>

CafeManagerWindow::CafeManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CafeManagerWindow)
{
    ui->setupUi(this);

    ui->chefText->setEnabled(false);
    ui->cashierText->setEnabled(false);
    ui->waiterText->setEnabled(false);

    QStringList slotHeaders;
    slotHeaders << "SlotID" << "Date" << "Start Time" << "End Time";

    QStringList bidHeaders;
    bidHeaders << "BidID" << "Full Name" << "Role";


    ui->slotTable->setColumnCount(4);
    ui->slotTable->horizontalHeader()->setVisible(true);
    ui->slotTable->setHorizontalHeaderLabels(slotHeaders);
    ui->slotTable->verticalHeader()->setVisible(false);
    ui->slotTable->setSortingEnabled(true);
    ui->slotTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->slotTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->slotTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->slotTable->horizontalHeader()->setStretchLastSection(true);
    ui->slotTable->setColumnWidth(0,50);


    ui->bidTable->setColumnCount(3);
    ui->bidTable->setHorizontalHeaderLabels(bidHeaders);
    ui->bidTable->verticalHeader()->setVisible(false);
    ui->bidTable->setSortingEnabled(true);
    ui->bidTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->bidTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bidTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->bidTable->horizontalHeader()->setStretchLastSection(true);
    ui->bidTable->setColumnWidth(0,50);
    ui->bidTable->setColumnWidth(1,175);


    ui->staffTable->setColumnCount(3);
    ui->staffTable->setHorizontalHeaderLabels(bidHeaders);
    ui->staffTable->verticalHeader()->setVisible(false);
    ui->staffTable->setSortingEnabled(true);
    ui->staffTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->staffTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->staffTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->staffTable->horizontalHeader()->setStretchLastSection(true);
    ui->staffTable->setColumnWidth(0,50);
    ui->staffTable->setColumnWidth(1,175);

    ui->chefTable->setColumnCount(3);
    ui->chefTable->setHorizontalHeaderLabels(bidHeaders);
    ui->chefTable->verticalHeader()->setVisible(false);
    ui->chefTable->setSortingEnabled(true);
    ui->chefTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->chefTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->chefTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->chefTable->horizontalHeader()->setStretchLastSection(true);
    ui->chefTable->setColumnWidth(0,50);
    ui->chefTable->setColumnWidth(1,175);

    ui->waiterTable->setColumnCount(3);
    ui->waiterTable->setHorizontalHeaderLabels(bidHeaders);
    ui->waiterTable->verticalHeader()->setVisible(false);
    ui->waiterTable->setSortingEnabled(true);
    ui->waiterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->waiterTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->waiterTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->waiterTable->horizontalHeader()->setStretchLastSection(true);
    ui->waiterTable->setColumnWidth(0,50);
    ui->waiterTable->setColumnWidth(1,175);

    ui->cashierTable->setColumnCount(3);
    ui->cashierTable->setHorizontalHeaderLabels(bidHeaders);
    ui->cashierTable->verticalHeader()->setVisible(false);
    ui->cashierTable->setSortingEnabled(true);
    ui->cashierTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cashierTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cashierTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->cashierTable->horizontalHeader()->setStretchLastSection(true);
    ui->cashierTable->setColumnWidth(0,50);
    ui->cashierTable->setColumnWidth(1,175);

    connect(ui->actionLogout, &QAction::triggered, this, &CafeManagerWindow::OnLogoutTriggered);

}

CafeManagerWindow::~CafeManagerWindow()
{
    delete ui;
}

void CafeManagerWindow::OnLogoutTriggered()
{
    AuthWindow* AuthView;
    AuthView = new AuthWindow;
    AuthView->setStyleSheet("AuthWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
    AuthView->show();
    this->close();
}

void ClearTables(Ui::CafeManagerWindow* ui)
{
    ui->staffTable->clear();
    ui->bidTable->clear();
    ui->waiterTable->clear();
    ui->chefTable->clear();
    ui->cashierTable->clear();
}

void CafeManagerWindow::on_calendarWidget_clicked(const QDate &date)
{

    ui->dateEdit->setDate(date);

    Response<QVector<Slot>> searchResponse = SearchSlotByDayController(ui->calendarWidget->selectedDate()).Execute();

    if(searchResponse.Result == EDatabaseResult::EDR_SUCCESS && searchResponse.Data.size() > 0)
    {
        QMessageBox successMsgBox;
        successMsgBox.setWindowTitle("Success!"); // Set the window title
        successMsgBox.setText("Slot search successful: " + QString::number(searchResponse.Data.size()) + " results found."); // Set the text to display
        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

        // Show the message box as a modal dialog
        successMsgBox.exec();

        ui->slotTable->setRowCount(0);
        ui->slotTable->setSortingEnabled(false);
        for (auto& slot : searchResponse.Data)
        {
            ui->slotTable->setSortingEnabled(false);
            int row = ui->slotTable->rowCount();
            ui->slotTable->insertRow(row); // Insert a new row


            // Create a new item for each piece of data/*
            QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
            QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
            QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

            // Add those items to the table
            ui->slotTable->setItem(row, 0, slotID); // 1 is the column number for the Username
            ui->slotTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
            ui->slotTable->setItem(row, 2, startTime);  //3 is the column number for profile
            ui->slotTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
            ui->slotTable->setSortingEnabled(true);

        }
        ui->slotTable->setSortingEnabled(true);
    }
    if(searchResponse.Data.size() <= 0)
    {
        ClearTables(ui);
        QMessageBox warning;
        warning.setWindowTitle("No Results"); // Set the window title
        warning.setText("Worklot search found no results."); // Set the text to display
        warning.setIcon(QMessageBox::Warning); // Set an icon for the message box (optional)
        warning.exec();
    }
    if(searchResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        ClearTables(ui);
        QMessageBox warning;
        warning.setWindowTitle("Error"); // Set the window title
        warning.setText("Slot search encountered an error."); // Set the text to display
        warning.setIcon(QMessageBox::Critical); // Set an icon for the message box (optional)
        warning.exec();
    }
    ui->slotTable->setFocus();
    ui->slotTable->selectRow(0);
}

void SetRoleText(Slot slot, Ui::CafeManagerWindow* ui)
{
    ui->cashierText->setText(QString::number(slot.getCurCashiers()));
    ui->waiterText->setText(QString::number(slot.getCurWaiters()));
    ui->chefText->setText(QString::number(slot.getCurChefs()));




}

void ReloadTables(Slot slot, Ui::CafeManagerWindow* ui)
{
    Response<QVector<User>> userSearch = SearchWorkersBySlotIDController(slot.SlotID).Execute();
    Response<QVector<Bid>> bidSearch = SearchBidsBySlotIDController(slot.SlotID).Execute();


    ui->staffTable->setRowCount(0);
    ui->staffTable->setSortingEnabled(false);
    for (auto& u : userSearch.Data)
    {
        int row = ui->staffTable->rowCount();
        ui->staffTable->insertRow(row); // Insert a new row

        // Create a new item for each piece of data/*
        QTableWidgetItem *name = new QTableWidgetItem(u.getFullName());
        QTableWidgetItem *role = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(u.getESR())));
        QTableWidgetItem *bidid;

        for(int i = 0; i < bidSearch.Data.size(); i++)
        {
            if(bidSearch.Data[i].UserID == u.UserID)
            {
                bidid = new QTableWidgetItem(QString::number(bidSearch.Data[i].BidID));
            }
        }

        // Add those items to the table
        ui->staffTable->setItem(row, 0, bidid);
        ui->staffTable->setItem(row, 1, name); // 1 is the column number for the name
        ui->staffTable->setItem(row, 2, role); // 2 is the column number for the role

    }
    ui->staffTable->setSortingEnabled(true);



    ui->bidTable->setRowCount(0);
    ui->chefTable->setRowCount(0);
    ui->waiterTable->setRowCount(0);
    ui->cashierTable->setRowCount(0);
    ui->bidTable->setSortingEnabled(false);
    ui->chefTable->setSortingEnabled(false);
    ui->waiterTable->setSortingEnabled(false);
    ui->cashierTable->setSortingEnabled(false);
    for(auto&b : bidSearch.Data)
    {
        if(b.EBS == 0)
        {
            Response<User> bidder = GetUserByBidIDController(b.BidID).Execute();
            int row = ui->bidTable->rowCount();
            ui->bidTable->insertRow(row); // Insert a new row



            // Create a new item for each piece of data/*
            //these pointers cannot be created in switch statements???? for some reason??
            //items also cannot be owned by multiple tables...so we create multiple copies here
            QTableWidgetItem *id = new QTableWidgetItem(QString::number(b.getBidID()));
            QTableWidgetItem *name = new QTableWidgetItem(bidder.Data.getFullName());
            QTableWidgetItem *role = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(bidder.Data.getESR())));
            QTableWidgetItem *chefid = new QTableWidgetItem(QString::number(b.getBidID()));
            QTableWidgetItem *chefName = new QTableWidgetItem(bidder.Data.getFullName());
            QTableWidgetItem *chefRole = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(bidder.Data.getESR())));
            QTableWidgetItem *cashierid = new QTableWidgetItem(QString::number(b.getBidID()));
            QTableWidgetItem *cashierName = new QTableWidgetItem(bidder.Data.getFullName());
            QTableWidgetItem *cashierRole = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(bidder.Data.getESR())));
            QTableWidgetItem *waiterid = new QTableWidgetItem(QString::number(b.getBidID()));
            QTableWidgetItem *waiterName = new QTableWidgetItem(bidder.Data.getFullName());
            QTableWidgetItem *waiterRole = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(bidder.Data.getESR())));

            // Add those items to the table
            ui->bidTable->setItem(row, 0, id);
            ui->bidTable->setItem(row, 1, name); // 1 is the column number for the name
            ui->bidTable->setItem(row, 2, role); // 2 is the column number for the role

            switch(bidder.Data.getESR())
            {
            case 1:
                ui->chefTable->insertRow(row); // Insert a new row
                ui->chefTable->setItem(row, 0, chefid);
                ui->chefTable->setItem(row, 1, chefName);
                ui->chefTable->setItem(row, 2, chefRole);
                delete waiterid;
                delete waiterName;
                delete waiterRole;
                delete cashierid;
                delete cashierName;
                delete cashierRole;
                break;
            case 2:
                ui->cashierTable->insertRow(row); // Insert a new row
                ui->cashierTable->setItem(row, 0, cashierid);
                ui->cashierTable->setItem(row, 1, cashierName);
                ui->cashierTable->setItem(row, 2, cashierRole);
                delete waiterid;
                delete waiterName;
                delete waiterRole;
                delete chefid;
                delete chefName;
                delete chefRole;
                break;
            case 3:
                ui->waiterTable->insertRow(row); // Insert a new row
                ui->waiterTable->setItem(row, 0, waiterid);
                ui->waiterTable->setItem(row, 1, waiterName);
                ui->waiterTable->setItem(row, 2, waiterRole);
                delete chefid;
                delete chefName;
                delete chefRole;
                delete cashierid;
                delete cashierName;
                delete cashierRole;
                break;
            default:
                break;
            }
        }

    }

    ui->bidTable->setSortingEnabled(true);
    ui->chefTable->setSortingEnabled(true);
    ui->waiterTable->setSortingEnabled(true);
    ui->cashierTable->setSortingEnabled(true);


}


void CafeManagerWindow::on_slotTable_itemSelectionChanged()
{
    // Check if the index is valid
    if (!ui->slotTable->currentIndex().isValid() || ui->slotTable->rowCount() <= 0 )
    {
        return;
    }

    Response<Slot> slotResponse = GetSlotController(ui->slotTable->item(ui->slotTable->currentRow(), 0)->text().toInt()).Execute();

    if(slotResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        return;
    }

    ReloadTables(slotResponse.Data, ui);
    SetRoleText(slotResponse.Data, ui);
}


void CafeManagerWindow::on_unapproveButton_clicked()
{

}


void CafeManagerWindow::on_approveButton_clicked()
{
    if (!ui->bidTable->currentIndex().isValid() || ui->bidTable->rowCount() <= 0 )
    {
        //nothing selected error
        return;
    }

    int row = ui->bidTable->currentIndex().row();
    int bidID = ui->bidTable->item(row, 0)->text().toInt();

    auto bidder = GetUserByBidIDController(bidID).Execute();
    auto bidderSlots = SearchSlotsByUserIDController(bidder.Data.UserID).Execute();


    if(bidder.Data.getMaxSlots() > bidderSlots.Data.size())
    {
        auto approveResponse = ApproveBidController(bidID).Execute();

        if(approveResponse.Result == EDatabaseResult::EDR_FAILURE)
        {
                //query error
        }

        int row = ui->slotTable->currentIndex().row();
        auto thisSlot = GetSlotController(ui->slotTable->item(row, 0)->text().toInt()).Execute();
        ReloadTables(thisSlot.Data, ui);
        SetRoleText(thisSlot.Data, ui);
    }
    else
    {
        //max slots error
    }
}

