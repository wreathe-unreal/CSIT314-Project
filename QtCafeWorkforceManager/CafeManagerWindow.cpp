#include "AuthWindow.h"
#include "CafeManagerWindow.h"
#include "Controller.h"
#include "Enums.h"
#include "PopUp.h"
#include "Response.h"
#include "Slot.h"
#include "ui_CafeManagerWindow.h"

#include <QMessageBox>

void ClearTables(Ui::CafeManagerWindow* ui)
{
    ui->staffTable->clear();
    ui->bidTable->clear();
    ui->waiterTable->clear();
    ui->chefTable->clear();
    ui->cashierTable->clear();
    ui->idleStaffTable->clear();
}

CafeManagerWindow::CafeManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CafeManagerWindow)
{
    ui->setupUi(this);

    ui->tabWidget->tabBar()->setTabTextColor(5, QColor("red"));
    ui->tabWidget->tabBar()->setStyleSheet(QString("QTabBar::tab:selected { background-color: dodgerblue; }"));

    ui->chefText->setEnabled(false);
    ui->cashierText->setEnabled(false);
    ui->waiterText->setEnabled(false);

    QStringList slotHeaders;
    slotHeaders << "SlotID" << "Date" << "Start Time" << "End Time";

    QStringList bidHeaders;
    bidHeaders << "BidID" << "Full Name" << "Role";

    QStringList idleHeaders;
    idleHeaders << "UserID" << "Full Name" << "Role";


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


    // Setup column and properties first
    ui->idleStaffTable->setColumnCount(3);
    ui->idleStaffTable->setHorizontalHeaderLabels(idleHeaders);
    ui->idleStaffTable->verticalHeader()->setVisible(false);
    ui->idleStaffTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->idleStaffTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idleStaffTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->idleStaffTable->horizontalHeader()->setStretchLastSection(true);
    ui->idleStaffTable->setColumnWidth(0,50);
    ui->idleStaffTable->setColumnWidth(1,175);

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

    ui->rejectedTable->setColumnCount(3);
    ui->rejectedTable->setHorizontalHeaderLabels(bidHeaders);
    ui->rejectedTable->verticalHeader()->setVisible(false);
    ui->rejectedTable->setSortingEnabled(true);
    ui->rejectedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rejectedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->rejectedTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->rejectedTable->horizontalHeader()->setStretchLastSection(true);
    ui->rejectedTable->setColumnWidth(0,50);
    ui->rejectedTable->setColumnWidth(1,175);

    Response<QVector<Slot>> slotResponse = GetSlotsController().Execute();

    if(slotResponse.Result == EDatabaseResult::EDR_SUCCESS && slotResponse.Data.size() > 0)
    {

        ui->slotTable->setRowCount(0);
        ui->slotTable->setSortingEnabled(false);
        for (auto& slot : slotResponse.Data)
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
    if(slotResponse.Data.size() <= 0)
    {
        ClearTables(ui);
        PopUp dialogBox;
        dialogBox.ManagerSearchEmptyError();
    }

    if(slotResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        ClearTables(ui);
        PopUp dialogBox;
        dialogBox.ManagerSearchError();
    }

    ui->slotTable->setFocus();
    ui->slotTable->selectRow(0);

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

void CafeManagerWindow::on_calendarWidget_clicked(const QDate &date)
{

    ui->dateEdit->setDate(date);

    Response<QVector<Slot>> searchResponse = SearchSlotsByQDateController::Invoke(ui->calendarWidget->selectedDate());

    if(searchResponse.Result == EDatabaseResult::EDR_SUCCESS && searchResponse.Data.size() > 0)
    {
        PopUp dialogBox;
        dialogBox.StaffSlotSearchResult(QString::number(searchResponse.Data.size()));


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
        PopUp dialogBox;
        dialogBox.ManagerSearchEmptyError();
    }
    if(searchResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        ClearTables(ui);
        PopUp dialogBox;
        dialogBox.ManagerSearchError();
    }
    ui->slotTable->setFocus();
    ui->slotTable->selectRow(0);
}

void ReloadTables(Ui::CafeManagerWindow* ui)
{


    int slotRow = ui->slotTable->currentIndex().row();
    Response<Slot> thisSlot = GetSlotController::Invoke(ui->slotTable->item(slotRow, 0)->text().toInt());

    Response<QVector<User>> staffSearch = GetStaffController::Invoke(thisSlot.Data.SlotID);
    Response<QVector<Bid>> bidSearch = SearchBidsBySlotIDController::Invoke(thisSlot.Data.SlotID);
    Response<QVector<User>> idleSearch = GetIdleStaffController::Invoke(thisSlot.Data.SlotID);

    qDebug() << "slot#" << thisSlot.Data.SlotID;
    qDebug() << "Staff Size: " << staffSearch.Data.size();
    qDebug() << "Idle Staff Size: " << idleSearch.Data.size();

    ui->idleStaffTable->setRowCount (0);
    ui->idleStaffTable->setSortingEnabled(false);
    for (auto& u : idleSearch.Data)
    {
        int row = ui->idleStaffTable->rowCount();
        ui->idleStaffTable->insertRow(row); // Insert a new row

        QTableWidgetItem *name = new QTableWidgetItem(u.getFullName());
        QTableWidgetItem *role = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(u.getESR())));
        QTableWidgetItem *userid = new QTableWidgetItem(QString::number(u.UserID));

        // Add those items to the table
        ui->idleStaffTable->setItem(row, 0, userid);
        ui->idleStaffTable->setItem(row, 1, name); // 1 is the column number for the name
        ui->idleStaffTable->setItem(row, 2, role); // 2 is the column number for the role

    }
    ui->idleStaffTable->setSortingEnabled(true);
    ui->idleStaffTable->horizontalHeader()->setVisible(true);


    ui->staffTable->setRowCount(0);
    ui->staffTable->setSortingEnabled(false);
    int NumChefs = 0;
    int NumCashiers = 0;
    int NumWaiters = 0;

    for (auto& u : staffSearch.Data)
    {
        int row = ui->staffTable->rowCount();
        ui->staffTable->insertRow(row); // Insert a new row

        // Create a new item for each piece of data/*
        QTableWidgetItem *name = new QTableWidgetItem(u.getFullName());
        QTableWidgetItem *role = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(u.getESR())));
        QTableWidgetItem *bidid = new QTableWidgetItem("");

        for(int i = 0; i < bidSearch.Data.size(); i++)
        {
            if(bidSearch.Data[i].UserID == u.UserID)
            {
                bidid = new QTableWidgetItem(QString::number(bidSearch.Data[i].BidID));
            }
        }

        switch(u.ESR)
        {
        case 0:
            break;
        case 1:
            NumChefs++;
            break;
        case 2:
            NumCashiers++;
            break;
        case 3:
            NumWaiters++;
            break;
        default:
            break;
        }

        // Add those items to the table
        ui->staffTable->setItem(row, 0, bidid);
        ui->staffTable->setItem(row, 1, name);
        ui->staffTable->setItem(row, 2, role);

    }
    ui->staffTable->setSortingEnabled(true);

    // Helper lambda function to determine color based on value
    auto determineColor = [](int value) -> QString { return (value == 0) ? "maroon" : "seagreen"; };

    // Cashier Text
    ui->cashierText->setText(QString::number(NumCashiers));
    ui->cashierText->setStyleSheet(QString("background-color: %1; color: white;").arg(determineColor(NumCashiers)));

    // Waiter Text
    ui->waiterText->setText(QString::number(NumWaiters));
    ui->waiterText->setStyleSheet(QString("background-color: %1; color: white;").arg(determineColor(NumWaiters)));

    // Chef Text
    ui->chefText->setText(QString::number(NumChefs));
    ui->chefText->setStyleSheet(QString("background-color: %1; color: white;").arg(determineColor(NumChefs)));



    ui->bidTable->setRowCount(0);
    ui->chefTable->setRowCount(0);
    ui->waiterTable->setRowCount(0);
    ui->cashierTable->setRowCount(0);
    ui->rejectedTable->setRowCount(0);
    ui->bidTable->setSortingEnabled(false);
    ui->chefTable->setSortingEnabled(false);
    ui->waiterTable->setSortingEnabled(false);
    ui->cashierTable->setSortingEnabled(false);
    ui->rejectedTable->setSortingEnabled(false);
    for(auto& b : bidSearch.Data)
    {
        Response<User> bidder = GetUserByBidIDController::Invoke(b.BidID);

        QTableWidgetItem *id = new QTableWidgetItem(QString::number(b.getBidID()));
        QTableWidgetItem *name = new QTableWidgetItem(bidder.Data.getFullName());
        QTableWidgetItem *role = new QTableWidgetItem(EStaffRoleToQString(static_cast<EStaffRole>(bidder.Data.getESR())));

        if(b.EBS == 0)
        {
            int bidRow = ui->bidTable->rowCount();
            ui->bidTable->insertRow(bidRow);
            ui->bidTable->setItem(bidRow, 0, new QTableWidgetItem(*id));
            ui->bidTable->setItem(bidRow, 1, new QTableWidgetItem(*name));
            ui->bidTable->setItem(bidRow, 2, new QTableWidgetItem(*role));

            switch(bidder.Data.getESR())
            {
            case 1:
            {// Chef
                int chefRow = ui->chefTable->rowCount();
                ui->chefTable->insertRow(chefRow);
                ui->chefTable->setItem(chefRow, 0, new QTableWidgetItem(*id));
                ui->chefTable->setItem(chefRow, 1, new QTableWidgetItem(*name));
                ui->chefTable->setItem(chefRow, 2, new QTableWidgetItem(*role));
                break;
            }
            case 2:
            {// Cashier
                int cashierRow = ui->cashierTable->rowCount();
                ui->cashierTable->insertRow(cashierRow);
                ui->cashierTable->setItem(cashierRow, 0, new QTableWidgetItem(*id));
                ui->cashierTable->setItem(cashierRow, 1, new QTableWidgetItem(*name));
                ui->cashierTable->setItem(cashierRow, 2, new QTableWidgetItem(*role));
                break;
            }
            case 3:
            {// Waiter
                int waiterRow = ui->waiterTable->rowCount();
                ui->waiterTable->insertRow(waiterRow);
                ui->waiterTable->setItem(waiterRow, 0, new QTableWidgetItem(*id));
                ui->waiterTable->setItem(waiterRow, 1, new QTableWidgetItem(*name));
                ui->waiterTable->setItem(waiterRow, 2, new QTableWidgetItem(*role));
                break;
            }
            default:
                break;
            }
        }
        else if(b.EBS == 2)
        {
            int rejectedRow = ui->rejectedTable->rowCount();
            ui->rejectedTable->insertRow(rejectedRow);
            ui->rejectedTable->setItem(rejectedRow, 0, id);
            ui->rejectedTable->setItem(rejectedRow, 1, name);
            ui->rejectedTable->setItem(rejectedRow, 2, role);
        }
    }

    ui->bidTable->setSortingEnabled(true);
    ui->chefTable->setSortingEnabled(true);
    ui->waiterTable->setSortingEnabled(true);
    ui->cashierTable->setSortingEnabled(true);
    ui->rejectedTable->setSortingEnabled(true);
}


void CafeManagerWindow::on_slotTable_itemSelectionChanged()
{
    // Check if the index is valid
    if (!ui->slotTable->currentIndex().isValid() || ui->slotTable->rowCount() <= 0 )
    {
        return;
    }

    Response<Slot> slotResponse = GetSlotController::Invoke(ui->slotTable->item(ui->slotTable->currentRow(), 0)->text().toInt());

    if(slotResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        return;
    }

    ReloadTables(ui);
}


void CafeManagerWindow::on_unapproveButton_clicked()
{

    if (!ui->staffTable->currentIndex().isValid() || ui->staffTable->rowCount() <= 0 )
    {
        PopUp error = PopUp();
        error.ManagerNullSelectionError();
        return;
    }

    int row = ui->staffTable->currentIndex().row();
    int bidID = ui->staffTable->item(row, 0)->text().toInt();

    Response<void> unapproveResponse = UnapproveBidController::Invoke(bidID);

    if(unapproveResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error = PopUp();
        error.ManagerUnapprovalError();
    }


    ReloadTables(ui);
}


void CafeManagerWindow::on_approveButton_clicked()
{

    Approve(ui->bidTable, ui);
    ReloadTables(ui);

}


void CafeManagerWindow::on_showWorkslotsButton_clicked()
{

    Response<QVector<Slot>> slotResponse = GetSlotsController().Execute();

    if(slotResponse.Result == EDatabaseResult::EDR_SUCCESS && slotResponse.Data.size() > 0)
    {

        ui->slotTable->setRowCount(0);
        ui->slotTable->setSortingEnabled(false);
        for (auto& slot : slotResponse.Data)
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
    if(slotResponse.Data.size() <= 0)
    {
        ClearTables(ui);
        PopUp dialogBox;
        dialogBox.ManagerSearchEmptyError();
    }

    if(slotResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        ClearTables(ui);
        PopUp dialogBox;
        dialogBox.ManagerSearchError();
    }

    ui->slotTable->setFocus();
    ui->slotTable->selectRow(0);

}


void CafeManagerWindow::on_rejectButton_clicked()
{
    Reject(ui->bidTable, ui);
    ReloadTables(ui);
}

void CafeManagerWindow::Reject(QTableWidget* tableWidget, Ui::CafeManagerWindow* ui)
{
    if (!tableWidget->currentIndex().isValid() || tableWidget->rowCount() <= 0)
    {
        PopUp error = PopUp();
        error.ManagerNullSelectionError();
        return;
    }

    int row = tableWidget->currentIndex().row();
    int bidID = tableWidget->item(row, 0)->text().toInt();

    auto bidder = GetUserByBidIDController::Invoke(bidID);

    Response<void> rejectResponse = RejectBidController::Invoke(bidID);

    if(rejectResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error = PopUp();
        error.ManagerRejectError();
    }
}

void CafeManagerWindow::Approve(QTableWidget* tableWidget, Ui::CafeManagerWindow* ui)
{

    if (!tableWidget->currentIndex().isValid() || tableWidget->rowCount() <= 0 )
    {
        PopUp error = PopUp();
        error.ManagerNullSelectionError();
        return;
    }

    int row = tableWidget->currentIndex().row();
    int bidID = tableWidget->item(row, 0)->text().toInt();

    Response<User> bidder = GetUserByBidIDController::Invoke(bidID);
    Response<QVector<Slot>> bidderSlots = SearchSlotsByUserIDController::Invoke(bidder.Data.UserID);


    if(bidder.Data.getMaxSlots() >= bidderSlots.Data.size())
    {
        Response<void> approveResponse = ApproveBidController::Invoke(bidID);
        if(approveResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
            return;
        }
            PopUp error = PopUp();
            error.ManagerApprovalError();
    }
    else
    {
        PopUp error = PopUp();
        error.ManagerMaxSlotsError();
    }
}

void CafeManagerWindow::Assign(QTableWidget* tableWidget, Ui::CafeManagerWindow* ui, Bid newBid)
{

    if (!tableWidget->currentIndex().isValid() || tableWidget->rowCount() <= 0 )
    {
        PopUp error = PopUp();
        error.ManagerNullSelectionError();
        return;
    }
    auto bidder = GetUserByBidIDController::Invoke(newBid.BidID);
    auto bidderSlots = SearchSlotsByUserIDController::Invoke(bidder.Data.UserID);


    if(bidder.Data.getMaxSlots() > bidderSlots.Data.size())
    {
        Response<void> approveResponse = ApproveBidController::Invoke(newBid.BidID);

        if(approveResponse.Result == EDatabaseResult::EDR_FAILURE)
        {
            PopUp error = PopUp();
            error.ManagerApprovalError();
        }
    }
    else
    {
        DeleteBidController::Invoke(newBid.BidID);
        PopUp error = PopUp();
        error.ManagerMaxSlotsError();
    }
}

void CafeManagerWindow::on_chefRejectButton_clicked()
{
    Reject(ui->chefTable, ui);
    ReloadTables(ui);
}


void CafeManagerWindow::on_cashierRejectButton_clicked()
{
    Reject(ui->cashierTable, ui);
    ReloadTables(ui);
}


void CafeManagerWindow::on_waiterRejectButton_clicked()
{
    Reject(ui->waiterTable, ui);
    ReloadTables(ui);
}


void CafeManagerWindow::on_rejectedUnreject_clicked()
{
    if (!ui->rejectedTable->currentIndex().isValid() || ui->rejectedTable->rowCount() <= 0 )
    {
        PopUp error = PopUp();
        error.ManagerNullSelectionError();
        return;
    }

    int row = ui->rejectedTable->currentIndex().row();
    int bidID = ui->rejectedTable->item(row, 0)->text().toInt();

    auto bidder = GetUserByBidIDController::Invoke(bidID);

    Response<void> unapproveResponse = UnapproveBidController::Invoke(bidID);

    if(unapproveResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error = PopUp();
        error.ManagerUnapprovalError();
    }


    ReloadTables(ui);
}


void CafeManagerWindow::on_chefApproveButton_clicked()
{
    Approve(ui->chefTable, ui);
    ReloadTables(ui);
}


void CafeManagerWindow::on_cashierApproveButton_clicked()
{
    Approve(ui->cashierTable, ui);
    ReloadTables(ui);
}


void CafeManagerWindow::on_waiterApproveButton_clicked()
{
    Approve(ui->waiterTable, ui);
    ReloadTables(ui);
}


void CafeManagerWindow::on_rejectedApprove_clicked()
{
    Approve(ui->rejectedTable, ui);
    ReloadTables(ui);
}


void CafeManagerWindow::on_assignButton_clicked()
{
    Bid newBid;
    newBid.SlotID = ui->slotTable->item(ui->slotTable->currentRow(), 0)->text().toInt();
    newBid.UserID = ui->idleStaffTable->item(ui->idleStaffTable->currentRow(), 0)->text().toInt();
    newBid.EBS = 1;
    Response<void> bidResult = CreateBidController::Invoke(newBid);
    if(bidResult.Result == EDatabaseResult::EDR_SUCCESS)
    {
        Assign(ui->idleStaffTable, ui, newBid);
        ReloadTables(ui);
    }

}
