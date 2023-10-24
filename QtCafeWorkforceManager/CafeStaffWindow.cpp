#include "AuthWindow.h"
#include "CafeStaffWindow.h"
#include "Enums.h"
#include "QApplicationGlobal.h"
#include "ui_CafeStaffWindow.h"

#include <QMessageBox>


void ReloadSlots(Ui::CafeStaffWindow* ui)
{
    int userID = GetUserIDController(QApplicationGlobal::CurrentUsername).Execute();
    QVector<Slot> slotVector;
    if(QApplicationGlobal::UserDAO.Result == EDatabaseResult::EDR_SUCCESS)
    {
        slotVector = SearchSlotsByUserIDController(userID).Execute();
    }
    else
    {
        QApplicationGlobal::UserDAO.Result = EDatabaseResult::EDR_UNINITIALIZED;
        return;
    }
    if(QApplicationGlobal::SlotDAO.Result == EDatabaseResult::EDR_SUCCESS)
    {
        qDebug() << slotVector.size();
        for (auto& slot : slotVector)
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
    else
    {
        QApplicationGlobal::UserDAO.Result = EDatabaseResult::EDR_UNINITIALIZED;
        return;
    }

    QApplicationGlobal::UserDAO.Result = EDatabaseResult::EDR_UNINITIALIZED;
}


CafeStaffWindow::CafeStaffWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::CafeStaffWindow)
{
    ui->setupUi(this);
    connect(ui->actionLogout, &QAction::triggered, this, &CafeStaffWindow::OnLogoutTriggered);
    ui->assignedTable->setSortingEnabled(true);
    ui->assignedTable->setColumnCount(4);
    ui->assignedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->assignedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Get the horizontal header of the table widget
    QHeaderView* horizontalHeader = ui->assignedTable->horizontalHeader();

    // Set the stretchLastSection property
    horizontalHeader->setStretchLastSection(false);

    QStringList headers;
    headers << "Slot ID" << "Date" << "Start Time" << "End Time";

    ui->assignedTable->setHorizontalHeaderLabels(headers);

    EStaffRole esr = QApplicationGlobal::UserDAO.GetESR(QApplicationGlobal::CurrentUsername);

    if(QApplicationGlobal::UserDAO.Result == EDatabaseResult::EDR_FAILURE)
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

    ReloadSlots(ui);

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
