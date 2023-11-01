#include "BidDAO.h"
#include "Bid.h"
#include "QApplicationGlobal.h"
#include "Response.h"
#include <QMessageBox>

Response<Bid> BidDataAccessObject::GetBid(int bidID)
{
    Response<Bid> bidResponse;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Database Connection Failure");
        errorMsgBox.setText("Database connection failure.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        bidResponse.Result = EDatabaseResult::EDR_FAILURE;
        return bidResponse;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Bid WHERE BidID = :bidid");
    query.bindValue(":bidid", bidID);

    if (query.exec() && query.next())
    {
        Bid bid;
        bid.BidID = query.value("BidID").toInt();
        bid.UserID = query.value("UserID").toInt();
        bid.SlotID = query.value("SlotID").toInt();
        bid.EBS = query.value("EBS").toInt();

        bidResponse.Data = bid;
    }
    else
    {
        bidResponse.Result = EDatabaseResult::EDR_FAILURE;
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Access Failure");
        errorMsgBox.setText("Could not retrieve bid data!");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        qWarning() << "GetBid() ERROR: " << query.lastError().text();
        return bidResponse;
    }

    bidResponse.Result = EDatabaseResult::EDR_SUCCESS;
    return bidResponse;
}

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

Response<QVector<Bid> > BidDataAccessObject::GetBids()
{

    Response<QVector<Bid>> bidsResponse;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Database Connection Failure");
        errorMsgBox.setText("Database connection failure.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        bidsResponse.Result = EDatabaseResult::EDR_FAILURE;
        return bidsResponse;
    }

    QSqlQuery query("SELECT * FROM Bid");

    QVector<Bid> bids;
    while (query.next())
    {
        Bid bid;
        bid.BidID = query.value("BidID").toInt();
        bid.UserID = query.value("UserID").toInt();
        bid.SlotID = query.value("SlotID").toInt();
        bid.EBS = query.value("EBS").toInt();

        bids.append(bid);
    }

    if (bids.isEmpty())
    {
        bidsResponse.Result = EDatabaseResult::EDR_FAILURE;
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Bid Access Failure");
        errorMsgBox.setText("Could not retrieve bid data or there are no bids!");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        qWarning() << "GetAllBids() ERROR: " << query.lastError().text();
        return bidsResponse;
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

Response<QVector<Bid>> BidDataAccessObject::GetRejected(int UserID)
{
    Response <QVector<Bid>> response = QApplicationGlobal::BidDAO.SearchByUserID(UserID);
    QVector<Bid> rejected;
    for(auto& b : response.Data)
    {
        if(b.EBS == 2)
        {
            rejected.push_back(b);
        }
    }
    response.Data = rejected;
    return response;
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

Response<User> BidDataAccessObject::GetUserByBidID(int bidid)
{
    Response<User> response;

    if (!DATABASE.isOpen())
    {
        qWarning() << "Failed to open database:" << DATABASE.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    // Get UserID based on BidID
    QSqlQuery query(DATABASE);
    query.prepare("SELECT UserID FROM Bid WHERE BidID = :bidID");
    query.bindValue(":bidID", bidid);

    if (!query.exec())
    {
        qWarning() << "Query failed:" << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    while (query.next())
    {
        int userID = query.value(0).toInt();

        // Now retrieve user details based on UserID
        QSqlQuery userQuery(DATABASE);
        userQuery.prepare("SELECT * FROM User WHERE UserID = :userID");
        userQuery.bindValue(":userID", userID);

        if (userQuery.exec() && userQuery.next())
        {
            User user;
            user.UserID = userQuery.value("UserID").toInt();
            user.setUsername(userQuery.value("Username").toString());
            user.setPassword(userQuery.value("Password").toString());
            user.setEUP(userQuery.value("EUP").toInt());
            user.setESR(userQuery.value("ESR").toInt());
            user.setMaxSlots(userQuery.value("MaxSlots").toInt());
            user.setbActive(userQuery.value("bActive").toInt());
            user.setFullName(userQuery.value("FullName").toString());
            qDebug() << user.EUP;
            response.Data = user;
        }
        else
        {
            qWarning() << "User query failed:" << userQuery.lastError().text();
        }
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<QVector<User>> BidDataAccessObject::GetStaff(int slotID)
{
    Response<QVector<User>> response;
    QVector<User> users;

    // Check if the connection is open
    if(!DATABASE.isOpen())
    {
        // Handle error (maybe set some error status in the Response object)
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!");
        errorMsgBox.setText("Could not open DB.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query(DATABASE);
    query.prepare("SELECT UserID FROM Bid WHERE SlotID = :slotID AND EBS = 1");
    query.bindValue(":slotID", slotID);

    if(!query.exec())
    {
        // Handle error
        qDebug() << "Error getting users:" << query.lastError();
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!");
        errorMsgBox.setText("Could not get users associated with slot.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Returning the same response object here instead of creating a new one.
    }

    while(query.next())
    {
        int userID = query.value(0).toInt();
        Response<User> userResponse = GetUserController(userID).Execute();
        if(userResponse.Result == EDatabaseResult::EDR_SUCCESS) // Assuming you have an EDR_SUCCESS status
        {
            users.push_back(userResponse.Data);
        }
        // Otherwise, handle the error or continue
    }

    // Populate the QVector<User> and wrap it in a Response and return
    response.Data = users;
    // Set any other response attributes if necessary
    return response;
}

Response<QVector<User>> BidDataAccessObject::GetBidders(int slotID)
{
    Response<QVector<User>> response;
    QVector<User> users;

    // Check if the connection is open
    if(!DATABASE.isOpen())
    {
        // Handle error (maybe set some error status in the Response object)
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!");
        errorMsgBox.setText("Could not open DB.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query(DATABASE);
    query.prepare("SELECT UserID FROM Bid WHERE SlotID = :slotID");
    query.bindValue(":slotID", slotID);

    if(!query.exec())
    {
        // Handle error
        qDebug() << "Error getting users:" << query.lastError();
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!");
        errorMsgBox.setText("Could not get users associated with slot.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Returning the same response object here instead of creating a new one.
    }

    while(query.next())
    {
        int userID = query.value(0).toInt();
        Response<User> userResponse = GetUserController(userID).Execute();
        if(userResponse.Result == EDatabaseResult::EDR_SUCCESS) // Assuming you have an EDR_SUCCESS status
        {
            users.push_back(userResponse.Data);
        }
        // Otherwise, handle the error or continue
    }

    // Populate the QVector<User> and wrap it in a Response and return
    response.Data = users;
    // Set any other response attributes if necessary
    return response;
}

Response<void> BidDataAccessObject::ApproveBid(int bidid)
{
    Response<void> response;
    if (!DATABASE.isOpen())
    {
        qWarning() << "Failed to open database:" << DATABASE.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query(DATABASE);
    query.prepare("UPDATE Bid SET EBS = 1 WHERE BidID = :bidID");
    query.bindValue(":bidID", bidid);

    if (!query.exec())
    {
        qWarning() << "Update failed:" << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response; // Update successful
}

Response<void> BidDataAccessObject::UnapproveBid(int bidid)
{
    Response<void> response;
    if (!DATABASE.isOpen())
    {
        qWarning() << "Failed to open database:" << DATABASE.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query(DATABASE);
    query.prepare("UPDATE Bid SET EBS = 0 WHERE BidID = :bidID");
    query.bindValue(":bidID", bidid);

    if (!query.exec())
    {
        qWarning() << "Update failed:" << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response; // Update successful
}

Response<void> BidDataAccessObject::RejectBid(int bidid)
{
    Response<void> response;
    if (!DATABASE.isOpen())
    {
        qWarning() << "Failed to open database:" << DATABASE.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query(DATABASE);
    query.prepare("UPDATE Bid SET EBS = 2 WHERE BidID = :bidID");
    query.bindValue(":bidID", bidid);

    if (!query.exec())
    {
        qWarning() << "Update failed:" << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response; // Update successful
}
