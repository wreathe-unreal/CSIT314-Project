#include "AuthWindow.h"
#include "CafeOwnerWindow.h"
#include "Controller.h"
#include "Slot.h"
#include "Response.h"
#include "qdatetime.h"
#include "ui_CafeOwnerWindow.h"
#include "PopUp.h"

#include <QMessageBox>

//rebuild tables, we calll this anytime we update a table so that our tables reflect the database properly
void CafeOwnerWindow::RebuildTable(QTableWidget* table)
{
    table->setRowCount(0);

    Response<QVector<Slot>> getSlotsResponse = GetSlotsController::Invoke();
    if(getSlotsResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        for (auto& slot : getSlotsResponse.Data)
        {
            table->setSortingEnabled(false);
            int row = table->rowCount();
            table->insertRow(row); // Insert a new row

            // Create a new item for each piece of data/*
            QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
            QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
            QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));

            // Add those items to the table
            table->setItem(row, 0, slotID);
            table->setItem(row, 1, date);
            table->setItem(row, 2, startTime);
            table->setItem(row, 3, endTime);
            table->setSortingEnabled(true);
        }
    }
}

//constructor
CafeOwnerWindow::CafeOwnerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CafeOwnerWindow)
{
    //attach ui pointer
    ui->setupUi(this);

    ui->slotTable->verticalHeader()->setVisible(false);

    ui->calendarEdit->setEnabled(false);
    ui->startEditEdit->setEnabled(false);
    ui->endEditEdit->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->editButton->setEnabled(false);

    ui->slotTable->setSortingEnabled(true);
    ui->slotTable->setColumnCount(4);
    ui->slotTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->slotTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Get the horizontal header of the table widget
    QHeaderView* horizontalHeader = ui->slotTable->horizontalHeader();

    // Set the stretchLastSection property
    horizontalHeader->setStretchLastSection(true);

    QStringList headers;
    headers << "Slot ID" << "Date" << "Start Time" << "End Time";

    ui->slotTable->setHorizontalHeaderLabels(headers);

    RebuildTable(ui->slotTable);

    connect(ui->actionLogout, &QAction::triggered, this, &CafeOwnerWindow::OnLogoutTriggered);
}

CafeOwnerWindow::~CafeOwnerWindow()
{
    delete ui;
}


//create slot button clicked
void CafeOwnerWindow::on_createButton_clicked()
{
    QDate date = ui->calendarCreate->selectedDate();
    QTime start = ui->startEdit->time();
    QTime end = ui->endEdit->time();
    Slot newSlot(date, start, end);

    Response<QVector<Slot>> createSlotResponse = CreateSlotController::Invoke(newSlot);

    //if create button suceeds
    if(createSlotResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        PopUp dialogBox = PopUp();
        dialogBox.OwnerSlotCreated();

        RebuildTable(ui->slotTable);

    }
    else //if it fails
    {
        PopUp error = PopUp();
        error.OwnerSlotCreateError();
    }
}


void CafeOwnerWindow::on_deleteButton_clicked()
{
    ui->calendarEdit->setEnabled(false);
    ui->startEditEdit->setEnabled(false);
    ui->endEditEdit->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);


    if(ui->slotTable->currentRow() == -1)
    {
        PopUp error = PopUp();
        error.OwnerSlotNullError();
        return;
    }

    // Display the confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Confirmation", "Are you sure you want to delete?",
                                  QMessageBox::Yes|QMessageBox::No);

    // Check which button was clicked
    if (reply == QMessageBox::Yes)
    {
        int slotIDToDelete = ui->slotTable->item(ui->slotTable->currentRow(), 0)->text().toInt();

        Response<void> deleteSlotResponse = DeleteSlotController::Invoke(slotIDToDelete);

        //if delete database response request suceeds
        if(deleteSlotResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
            PopUp dialogBox = PopUp();
            dialogBox.OwnerSlotDeleted();

            Response<QVector<Slot>> getSlotsResponse = GetSlotsController::Invoke();

            if(getSlotsResponse.Result == EDatabaseResult::EDR_SUCCESS)
            {
                RebuildTable(ui->slotTable);
            }
        }
        else
        {
            PopUp dialogBox = PopUp();
            dialogBox.OwnerSlotDeleteError();
        }
    }
}

//called when we click a new slot on the slot table
void CafeOwnerWindow::on_slotTable_clicked(const QModelIndex &index)
{
    // Check if the index is valid
    if (!index.isValid())
    {
        ui->calendarEdit->setEnabled(false);
        ui->startEditEdit->setEnabled(false);
        ui->endEditEdit->setEnabled(false);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        return;
    }

    // Get the selected row
    int row = index.row();


    ui->tabWidget->setCurrentIndex(1);
    // Retrieve the items from the table
    QTableWidgetItem *slotID = ui->slotTable->item(row, 0);
    QTableWidgetItem *date = ui->slotTable->item(row, 1);
    QTableWidgetItem *startTime = ui->slotTable->item(row, 2);
    QTableWidgetItem *endTime = ui->slotTable->item(row, 3);

    //set ui text for slot edit information

    ui->slotIDEdit->setText(slotID->text());

    ui->calendarEdit->setEnabled(true);
    ui->calendarEdit->setSelectedDate(QDate::fromString(date->text()));

    ui->startEditEdit->setEnabled(true);
    ui->startEditEdit->setTime(QTime::fromString(startTime->text(), "hh:mm:ss AP"));

    ui->endEditEdit->setEnabled(true);
    ui->endEditEdit->setTime(QTime::fromString(endTime->text(), "hh:mm:ss AP"));

    ui->editButton->setEnabled(true);

    ui->deleteButton->setEnabled(true);

}

//called when the edit button is clicked
void CafeOwnerWindow::on_editButton_clicked()
{
    if(ui->startEditEdit->time() >= ui->endEditEdit->time())
    {
        PopUp error = PopUp();
        error.OwnerSlotDurationError();
        return;
    }
    if(ui->slotTable->currentRow() == -1)
    {
        PopUp error = PopUp();
        error.OwnerSlotNullError();
        return;
    }


    Slot slotChanged;

    int row = ui->slotTable->currentRow();

    //we create the updated slot
    slotChanged.SlotID = ui->slotTable->item(row, 0)->text().toInt();
    slotChanged.Date = ui->calendarEdit->selectedDate();
    slotChanged.StartTime = ui->startEditEdit->time();
    slotChanged.EndTime = ui->endEditEdit->time();

    //if the database request to update the slot succeeds
    if(UpdateSlotController::Invoke(slotChanged).Result == EDatabaseResult::EDR_SUCCESS)
    {
        PopUp dialogBox= PopUp();
        dialogBox.OwnerSlotUpdated();

        ui->calendarEdit->setEnabled(false);
        ui->startEditEdit->setEnabled(false);
        ui->endEditEdit->setEnabled(false);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->slotIDEdit->clear();

        ui->slotTable->setRowCount(0);

        RebuildTable(ui->slotTable);
    }
    else
    {
        PopUp error = PopUp();
        error.OwnerSlotUpdateError();
    }
}


void CafeOwnerWindow::on_searchButton_clicked()
{

    //get the selected date from the calendar
    QDate searchDate = ui->calendarSearch->selectedDate();
    Response<QVector<Slot>> searchResponse = SearchSlotsByQDateController::Invoke(searchDate);

    //if the db request to search slots by the selected date
    if(SearchSlotsByQDateController::Invoke(searchDate).Result == EDatabaseResult::EDR_SUCCESS
        && SearchSlotsByQDateController::GetResponse().Data.size() > 0)
    {
        PopUp dialogBox = PopUp();
        dialogBox.OwnerSlotSearchResult(searchResponse.Data.size());

        ui->slotTable->setRowCount(0);

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
    }
    if(searchResponse.Data.size() <= 0)
    {
        QMessageBox warning;
        warning.setWindowTitle("No Results"); // Set the window title
        warning.setText("Slot search found no results."); // Set the text to display
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

//logout callback
void CafeOwnerWindow::OnLogoutTriggered()
{
    AuthWindow* AuthView;
    AuthView = new AuthWindow;
    AuthView->setStyleSheet("AuthWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
    AuthView->show();
    this->close();
}


//when show all workslots is clicked, simply rebuild the tables which will show all workslots
void CafeOwnerWindow::on_showAllButton_clicked()
{
    RebuildTable(ui->slotTable);
}



