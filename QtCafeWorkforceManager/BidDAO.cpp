#include "BidDAO.h"
#include "Bid.h"
#include "QApplicationGlobal.h"

#include <QMessageBox>

void BidDataAccessObject::Insert(Bid newBid)
{

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Check if the username already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT * FROM Bids WHERE UserID = :userid AND SlotID = :slotid");
    queryCheck.bindValue(":userid", newBid.getUserID());
    queryCheck.bindValue(":slotid", newBid.getSlotID());

    if (queryCheck.exec())
    {
        if (queryCheck.next() && queryCheck.value(0).toInt() > 0)
        {
            qDebug() << "Bid already exists.";
            QMessageBox errorMsgBox;
            errorMsgBox.setWindowTitle("Bid Conflict!"); // Set the window title
            errorMsgBox.setText("A bid for this workslot already exists!"); // Set the text to display
            errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
            errorMsgBox.exec();
            this->Result = EDatabaseResult::EDR_FAILURE;
        }
    }
    else
    {
        qWarning() << "Check existing bid query failed: " << queryCheck.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Insert the new user
    QSqlQuery queryInsert;
    queryInsert.prepare("INSERT INTO Bid (UserID, SlotID, EBS) VALUES (:userid, :slotid, :ebs)");
    queryInsert.bindValue(":userid", newBid.getUserID());
    queryInsert.bindValue(":slotid", newBid.getSlotID());
    queryInsert.bindValue(":ebs", newBid.getEBS());

    if (queryInsert.exec())
    {
        this->Result = EDatabaseResult::EDR_SUCCESS;
    }
    else
    {
        qWarning() << "Insert bid failed: " << queryInsert.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

}

QVector<Bid> BidDataAccessObject::GetPending()
{

    QVector<Bid> bids; // Vector to store the retrieved User objects

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Database Connection Failure"); // Set the window title
        errorMsgBox.setText("Database connection failure."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        Result = EDatabaseResult::EDR_FAILURE;
        return bids; // Return the empty vector
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Bid WHERE EBS = 0");

    if (query.exec())
    {
        while (query.next())
        {
            User user;
            Bid bid;
            bid.BidID = query.value("BidID").toInt();
            bid.UserID = query.value("UserID").toInt();
            bid.SlotID = query.value("SlotID").toInt();
            bid.EBS = query.value("EBS").toInt();

            bids.push_back(bid);
        }
    }
    else
    {
        Result = EDatabaseResult::EDR_FAILURE;
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Access Failure"); // Set the window title
        errorMsgBox.setText("Could not build pending bids table!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        qWarning() << "GetBids() ERROR: " << query.lastError().text();
    }

    Result = EDatabaseResult::EDR_SUCCESS;
    return bids;
}

QVector<Bid> BidDataAccessObject::SearchByUserID(int userID)
{


    QVector<Bid> bids; // Vector to store the retrieved User objects

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Database Connection Failure"); // Set the window title
        errorMsgBox.setText("Database connection failure."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        Result = EDatabaseResult::EDR_FAILURE;
        return bids; // Return the empty vector
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Bid WHERE UserID = :userid");
    query.bindValue(":userid", userID);

    if (query.exec())
    {
        while (query.next())
        {
            User user;
            Bid bid;
            bid.BidID = query.value("BidID").toInt();
            bid.UserID = query.value("UserID").toInt();
            bid.SlotID = query.value("SlotID").toInt();
            bid.EBS = query.value("EBS").toInt();

            bids.push_back(bid);
        }
    }
    else
    {
        Result = EDatabaseResult::EDR_FAILURE;
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Access Failure"); // Set the window title
        errorMsgBox.setText("Could not build users' bids table!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        qWarning() << "GetBids() ERROR: " << query.lastError().text();
    }

    Result = EDatabaseResult::EDR_SUCCESS;
    return bids;
}
