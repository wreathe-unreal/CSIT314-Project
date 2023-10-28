#include "BidDAO.h"
#include "Bid.h"
#include "QApplicationGlobal.h"
#include "Response.h"
#include <QMessageBox>

Response<void> BidDataAccessObject::Insert(Bid newBid)
{

    Response<void> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    // Check if the bid already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT * FROM Bid WHERE UserID = :userid AND SlotID = :slotid");
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
            response.Result = EDatabaseResult::EDR_FAILURE;
            return response;
        }
    }
    else
    {
        qWarning() << "Check existing bid query failed: " << queryCheck.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    // Insert the new user
    QSqlQuery queryInsert;
    queryInsert.prepare("INSERT INTO Bid (UserID, SlotID, EBS) VALUES (:userid, :slotid, :ebs)");
    queryInsert.bindValue(":userid", newBid.getUserID());
    queryInsert.bindValue(":slotid", newBid.getSlotID());
    queryInsert.bindValue(":ebs", newBid.getEBS());

    if (queryInsert.exec())
    {
        response.Result = EDatabaseResult::EDR_SUCCESS;
        return response;
    }
    else
    {
        qWarning() << "Insert bid failed: " << queryInsert.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

}

Response<QVector<Bid>> BidDataAccessObject::GetPending()
{
    Response<QVector<Bid>> bidResponse;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Database Connection Failure"); // Set the window title
        errorMsgBox.setText("Database connection failure."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        bidResponse.Result = EDatabaseResult::EDR_FAILURE;
        return bidResponse; // Return the empty vector
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

            bidResponse.Data.push_back(bid);
        }
    }
    else
    {
        bidResponse.Result = EDatabaseResult::EDR_FAILURE;
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Access Failure"); // Set the window title
        errorMsgBox.setText("Could not build pending bids table!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        qWarning() << "GetBids() ERROR: " << query.lastError().text();
        return bidResponse;
    }

    bidResponse.Result = EDatabaseResult::EDR_SUCCESS;
    return bidResponse;
}

Response<QVector<Bid>> BidDataAccessObject::SearchByUserID(int userID)
{
    Response<QVector<Bid>> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Database Connection Failure"); // Set the window title
        errorMsgBox.setText("Database connection failure."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Return the empty vector
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

            response.Data.push_back(bid);
        }
    }
    else
    {
        response.Result = EDatabaseResult::EDR_FAILURE;
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Access Failure"); // Set the window title
        errorMsgBox.setText("Could not build users' bids table!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        qWarning() << "GetBids() ERROR: " << query.lastError().text();
        return response;
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<QVector<Bid> > BidDataAccessObject::SearchBySlotID(int slotID)
{

    Response<QVector<Bid>> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Database Connection Failure"); // Set the window title
        errorMsgBox.setText("Database connection failure."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Return the empty vector
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Bid WHERE SlotID = :slotid");
    query.bindValue(":slotid", slotID);

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

            response.Data.push_back(bid);
        }
    }
    else
    {
        response.Result = EDatabaseResult::EDR_FAILURE;
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Access Failure"); // Set the window title
        errorMsgBox.setText("Could not build slots' bids table!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        qWarning() << "GetBids() ERROR: " << query.lastError().text();
        return response;
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}


Response<void> BidDataAccessObject::Delete(int bidID)
{

    Response<void> response;

    if (!DATABASE.open())
    {
        response.Result = EDatabaseResult::EDR_FAILURE;
        qDebug() << "Error: Unable to open the database.";
        return response;
    }

    QSqlQuery query;

    // Prepare SQL statement to delete user with the given username
    query.prepare("DELETE FROM Bid WHERE BidID = :bidid");

    query.bindValue(":bidid", bidID);

    if (!query.exec())
    {
        response.Result = EDatabaseResult::EDR_FAILURE;
        qDebug() << "Error: Failed to delete user. Error:" << query.lastError().text();
        return response;
    }

    if (query.numRowsAffected() == 0)
    {
        response.Result = EDatabaseResult::EDR_FAILURE;
        qDebug() << "No bids found with the bidID.";
        return response;
    }
    else
    {
        response.Result = EDatabaseResult::EDR_SUCCESS;
        return response;
    }
}
