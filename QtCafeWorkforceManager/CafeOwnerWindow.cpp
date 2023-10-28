#include "AuthWindow.h"
#include "CafeOwnerWindow.h"
#include "Controller.h"
#include "QApplicationGlobal.h"
#include "Slot.h"
#include "Response.h"
#include "qdatetime.h"
#include "ui_CafeOwnerWindow.h"

#include <QMessageBox>

CafeOwnerWindow::CafeOwnerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CafeOwnerWindow)
{
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    ui->calendarEdit->setEnabled(false);
    ui->startEditEdit->setEnabled(false);
    ui->endEditEdit->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->editButton->setEnabled(false);

    ui->slotTable->setSortingEnabled(true);
    ui->slotTable->setColumnCount(7);
    ui->slotTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->slotTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Get the horizontal header of the table widget
    QHeaderView* horizontalHeader = ui->slotTable->horizontalHeader();

    // Set the stretchLastSection property
    horizontalHeader->setStretchLastSection(true);

    QStringList headers;
    headers << "Slot ID" << "Date" << "Start Time" << "End Time" << " Current Chefs" << "Current Cashiers" << "Current Waiters";

    ui->slotTable->setHorizontalHeaderLabels(headers);
    int chefsColumnIndex = 4; // Index of "Current Chefs" column
    int cashiersColumnIndex = 5; // Index of "Current Cashiers" column
    int waitersColumnIndex = 6; // Index of "Current Waiters" column

    int smallerWidth = 100; // Choose a width that fits your needs

    ui->slotTable->setColumnWidth(chefsColumnIndex, smallerWidth);
    ui->slotTable->setColumnWidth(cashiersColumnIndex, smallerWidth);
    ui->slotTable->setColumnWidth(waitersColumnIndex, smallerWidth);

    Response<QVector<Slot>> slotResponse = GetSlotsController().Execute();
    if(slotResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
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
            QTableWidgetItem *curChefs = new QTableWidgetItem(QString::number(slot.getCurChefs()));
            QTableWidgetItem *curCashiers = new QTableWidgetItem(QString::number(slot.getCurCashiers()));
            QTableWidgetItem *curWaiters = new QTableWidgetItem(QString::number(slot.getCurWaiters()));

            // Add those items to the table
            ui->slotTable->setItem(row, 0, slotID); // 1 is the column number for the Username
            ui->slotTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
            ui->slotTable->setItem(row, 2, startTime);  //3 is the column number for profile
            ui->slotTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
            ui->slotTable->setItem(row, 4, curChefs);
            ui->slotTable->setItem(row, 5, curCashiers);
            ui->slotTable->setItem(row, 6, curWaiters);
            ui->slotTable->setSortingEnabled(true);
        }
    }

    connect(ui->actionLogout, &QAction::triggered, this, &CafeOwnerWindow::OnLogoutTriggered);
}

CafeOwnerWindow::~CafeOwnerWindow()
{
    delete ui;
}


void CafeOwnerWindow::on_createButton_clicked()
{
    QDate date = ui->calendarCreate->selectedDate();
    QTime start = ui->startEdit->time();
    QTime end = ui->endEdit->time();
    Slot newSlot(date, start, end);

    Response<QVector<Slot>> createSlotResponse = CreateSlotController(newSlot).Execute();

    if(createSlotResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        QMessageBox successMsgBox;
        successMsgBox.setWindowTitle("Success!"); // Set the window title
        successMsgBox.setText("Work slot has been created."); // Set the text to display
        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

        // Show the message box as a modal dialog
        successMsgBox.exec();

        ui->slotTable->setRowCount(0);

        for (auto& slot : createSlotResponse.Data)
        {
            ui->slotTable->setSortingEnabled(false);
            int row = ui->slotTable->rowCount();
            ui->slotTable->insertRow(row); // Insert a new row


            // Create a new item for each piece of data/*
            QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
            QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
            QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *curChefs = new QTableWidgetItem(QString::number(slot.getCurChefs()));
            QTableWidgetItem *curCashiers = new QTableWidgetItem(QString::number(slot.getCurCashiers()));
            QTableWidgetItem *curWaiters = new QTableWidgetItem(QString::number(slot.getCurWaiters()));

            // Add those items to the table
            ui->slotTable->setItem(row, 0, slotID); // 1 is the column number for the Username
            ui->slotTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
            ui->slotTable->setItem(row, 2, startTime);  //3 is the column number for profile
            ui->slotTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
            ui->slotTable->setItem(row, 4, curChefs);
            ui->slotTable->setItem(row, 5, curCashiers);
            ui->slotTable->setItem(row, 6, curWaiters);
            ui->slotTable->setSortingEnabled(true);
        }
    }
    else
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("The work slot could not be created."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
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
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("No work slot selected!"); // Set the text to display
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
        int slotIDToDelete = ui->slotTable->item(ui->slotTable->currentRow(), 0)->text().toInt();

        Response<void> deleteSlotResponse = DeleteSlotController(slotIDToDelete).Execute();

        if(deleteSlotResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
            QMessageBox successMsgBox;
            successMsgBox.setWindowTitle("Success!"); // Set the window title
            successMsgBox.setText("Slot has been deleted."); // Set the text to display
            successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

            // Show the message box as a modal dialog
            successMsgBox.exec();

            Response<QVector<Slot>> getSlotsResponse = GetSlotsController().Execute();

            if(getSlotsResponse.Result == EDatabaseResult::EDR_SUCCESS)
            {
                ui->slotTable->setRowCount(0);

                for (auto& slot : getSlotsResponse.Data)
                {
                    ui->slotTable->setSortingEnabled(false);
                    int row = ui->slotTable->rowCount();
                    ui->slotTable->insertRow(row); // Insert a new row


                    // Create a new item for each piece of data/*
                    QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
                    QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
                    QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
                    QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));
                    QTableWidgetItem *curChefs = new QTableWidgetItem(QString::number(slot.getCurChefs()));
                    QTableWidgetItem *curCashiers = new QTableWidgetItem(QString::number(slot.getCurCashiers()));
                    QTableWidgetItem *curWaiters = new QTableWidgetItem(QString::number(slot.getCurWaiters()));

                    // Add those items to the table
                    ui->slotTable->setItem(row, 0, slotID); // 1 is the column number for the Username
                    ui->slotTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
                    ui->slotTable->setItem(row, 2, startTime);  //3 is the column number for profile
                    ui->slotTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
                    ui->slotTable->setItem(row, 4, curChefs);
                    ui->slotTable->setItem(row, 5, curCashiers);
                    ui->slotTable->setItem(row, 6, curWaiters);
                    ui->slotTable->setSortingEnabled(true);
                }
            }
        }
        else
        {
            QMessageBox errorMsgBox;
            errorMsgBox.setWindowTitle("Error!"); // Set the window title
            errorMsgBox.setText("The slot could not be deleted."); // Set the text to display
            errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

            // Show the message box as a modal dialog
            errorMsgBox.exec();
        }
    }
}


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
    QTableWidgetItem *curChefs = ui->slotTable->item(row, 4);
    QTableWidgetItem *curCashiers = ui->slotTable->item(row, 5);
    QTableWidgetItem *curWaiters = ui->slotTable->item(row, 6);

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


void CafeOwnerWindow::on_editButton_clicked()
{
    if(ui->startEditEdit->time() >= ui->endEditEdit->time())
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("Work slot has no duration!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
        return;
    }
    if(ui->slotTable->currentRow() == -1)
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("No slot selected!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
        return;
    }

    Slot slotChanged;

    int row = ui->slotTable->currentRow();

    slotChanged.SlotID = ui->slotTable->item(row, 0)->text().toInt();
    slotChanged.Date = ui->calendarEdit->selectedDate();
    slotChanged.StartTime = ui->startEditEdit->time();
    slotChanged.EndTime = ui->endEditEdit->time();
    slotChanged.CurChefs = ui->slotTable->item(row, 4)->text().toInt();
    slotChanged.CurCashiers = ui->slotTable->item(row, 5)->text().toInt();
    slotChanged.CurWaiters = ui->slotTable->item(row, 6)->text().toInt();

    Response<QVector<Slot>> updateSlotsResponse = UpdateSlotController(slotChanged).Execute();

    if(updateSlotsResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        QMessageBox successMsgBox;
        successMsgBox.setWindowTitle("Success!"); // Set the window title
        successMsgBox.setText("Slot has been updated."); // Set the text to display
        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

        // Show the message box as a modal dialog
        successMsgBox.exec();

        ui->calendarEdit->setEnabled(false);
        ui->startEditEdit->setEnabled(false);
        ui->endEditEdit->setEnabled(false);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->slotIDEdit->clear();

        ui->slotTable->setRowCount(0);

        for (auto& slot : updateSlotsResponse.Data)
        {
            ui->slotTable->setSortingEnabled(false);
            int row = ui->slotTable->rowCount();
            ui->slotTable->insertRow(row); // Insert a new row


            // Create a new item for each piece of data/*
            QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
            QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
            QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *curChefs = new QTableWidgetItem(QString::number(slot.getCurChefs()));
            QTableWidgetItem *curCashiers = new QTableWidgetItem(QString::number(slot.getCurCashiers()));
            QTableWidgetItem *curWaiters = new QTableWidgetItem(QString::number(slot.getCurWaiters()));

            // Add those items to the table
            ui->slotTable->setItem(row, 0, slotID); // 1 is the column number for the Username
            ui->slotTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
            ui->slotTable->setItem(row, 2, startTime);  //3 is the column number for profile
            ui->slotTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
            ui->slotTable->setItem(row, 4, curChefs);
            ui->slotTable->setItem(row, 5, curCashiers);
            ui->slotTable->setItem(row, 6, curWaiters);
            ui->slotTable->setSortingEnabled(true);
        }

    }
    else
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("The slot could not be updated."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
    }
}


void CafeOwnerWindow::on_searchButton_clicked()
{
    Response<QVector<Slot>> searchResponse = SearchSlotByDayController(ui->calendarSearch->selectedDate()).Execute();

    if(searchResponse.Result == EDatabaseResult::EDR_SUCCESS && searchResponse.Data.size() > 0)
    {
        QMessageBox successMsgBox;
        successMsgBox.setWindowTitle("Success!"); // Set the window title
        successMsgBox.setText("Slot search successful: " + QString::number(searchResponse.Data.size()) + " results found."); // Set the text to display
        successMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box (optional)

        // Show the message box as a modal dialog
        successMsgBox.exec();

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
            QTableWidgetItem *curChefs = new QTableWidgetItem(QString::number(slot.getCurChefs()));
            QTableWidgetItem *curCashiers = new QTableWidgetItem(QString::number(slot.getCurCashiers()));
            QTableWidgetItem *curWaiters = new QTableWidgetItem(QString::number(slot.getCurWaiters()));

            // Add those items to the table
            ui->slotTable->setItem(row, 0, slotID); // 1 is the column number for the Username
            ui->slotTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
            ui->slotTable->setItem(row, 2, startTime);  //3 is the column number for profile
            ui->slotTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
            ui->slotTable->setItem(row, 4, curChefs);
            ui->slotTable->setItem(row, 5, curCashiers);
            ui->slotTable->setItem(row, 6, curWaiters);
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

void CafeOwnerWindow::OnLogoutTriggered()
{
    AuthWindow* AuthView;
    AuthView = new AuthWindow;
    AuthView->setStyleSheet("AuthWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
    AuthView->show();
    this->close();
}


void CafeOwnerWindow::on_showAllButton_clicked()
{
    ui->slotTable->setRowCount(0);
    Response<QVector<Slot>> getSlotsResponse = GetSlotsController().Execute();
    if(getSlotsResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        for (auto& slot : getSlotsResponse.Data)
        {
            ui->slotTable->setSortingEnabled(false);
            int row = ui->slotTable->rowCount();
            ui->slotTable->insertRow(row); // Insert a new row

            // Create a new item for each piece of data/*
            QTableWidgetItem *slotID = new QTableWidgetItem(QString::number(slot.getSlotID()));
            QTableWidgetItem *date = new QTableWidgetItem(slot.getDate().toString());
            QTableWidgetItem *startTime = new QTableWidgetItem(slot.getStartTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *endTime = new QTableWidgetItem(slot.getEndTime().toString("hh:mm:ss AP"));
            QTableWidgetItem *curChefs = new QTableWidgetItem(QString::number(slot.getCurChefs()));
            QTableWidgetItem *curCashiers = new QTableWidgetItem(QString::number(slot.getCurCashiers()));
            QTableWidgetItem *curWaiters = new QTableWidgetItem(QString::number(slot.getCurWaiters()));

            // Add those items to the table
            ui->slotTable->setItem(row, 0, slotID); // 1 is the column number for the Username
            ui->slotTable->setItem(row, 1, date); // 2 is the column number for the HashedPassword
            ui->slotTable->setItem(row, 2, startTime);  //3 is the column number for profile
            ui->slotTable->setItem(row, 3, endTime); // 4 is the column number for the Role etc
            ui->slotTable->setItem(row, 4, curChefs);
            ui->slotTable->setItem(row, 5, curCashiers);
            ui->slotTable->setItem(row, 6, curWaiters);
            ui->slotTable->setSortingEnabled(true);
        }
    }
}

