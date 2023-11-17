#include "Bid.h"
#include "QApplicationGlobal.h"
#include <QMessageBox>

Bid::Bid()
{

}

Bid::~Bid()
{

}

Bid::Bid(int bidID, int userID, int slotID)
{
    this->BidID = bidID;
    this->UserID = userID;
    this->SlotID = slotID;
}

int Bid::getBidID() const
{
    return this->BidID;
}

int Bid::getSlotID() const
{
    return this->SlotID;
}

void Bid::setBidID(int bidID)
{
    this->BidID = bidID;
}

void Bid::setSlotID(int slotID)
{
    this->SlotID = slotID;
}

int Bid::getUserID() const
{
    return this->UserID;
}

void Bid::setUserID(int newUserID)
{
    this->UserID = newUserID;
}

int Bid::getEBS() const
{
    return this->EBS;
}

void Bid::setEBS(int newEBS)
{
    this->EBS = newEBS;
}

Response<QVector<int>> Bid::GetSlotIDsByUserID(int userID)
{
    Response<QVector<int>> response;

    QSqlQuery query;
    // Get the SlotIDs from the Bid table where EBS = 1 for the given UserID
    query.prepare("SELECT SlotID FROM Bid WHERE UserID = ? AND EBS = 1");
    query.addBindValue(userID);
    if (!query.exec())
    {
        qWarning() << "Failed to execute Bid query:" << query.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    while (query.next())
    {
        int slotID = query.value(0).toInt();
        response.Data.push_back(slotID);
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

//gets a list of Bidder's UsersID based on a provided Slot ID
Response<QVector<int> > Bid::GetBiddersBySlotID(int slotID)
{
    Response<QVector<int>> response;

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
        // Handle errors
        qDebug() << "Erorr getting user IDS:" << query.lastError();
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!");
        errorMsgBox.setText("Could not get user IDs associated with bid SLOTID.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Returning the same response object here instead of creating a new one.
    }

    while(query.next())
    {
        int userID = query.value(0).toInt();

        response.Data.push_back(userID);
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<Bid> Bid::GetBid(int bidID)
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

Response<Bid> Bid::Insert(Bid newBid)
{

    Response<Bid> response;

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

    QSqlQuery queryInsert;
    queryInsert.prepare("INSERT INTO Bid (UserID, SlotID, EBS) VALUES (:userid, :slotid, :ebs)");
    queryInsert.bindValue(":userid", newBid.getUserID());
    queryInsert.bindValue(":slotid", newBid.getSlotID());
    queryInsert.bindValue(":ebs", newBid.getEBS());


    if (queryInsert.exec())
    {
        response.Result = EDatabaseResult::EDR_SUCCESS;
        for(auto b : Bid::GetBids().Data)
        {
            if(b.SlotID == newBid.getSlotID() && b.UserID == newBid.getUserID())
            {
                response.Data = b;
                break;
            }
        }
        return response;
    }
    else
    {
        qWarning() << "Insert bid failed: " << queryInsert.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

}

//gets all existing bids
Response<QVector<Bid> > Bid::GetBids()
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
    query.prepare("SELECT * FROM Bid");

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
        errorMsgBox.setText("Could not get bids!"); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box
        errorMsgBox.exec();
        qWarning() << "GetBids() ERROR: " << query.lastError().text();
        return bidResponse;
    }

    bidResponse.Result = EDatabaseResult::EDR_SUCCESS;
    return bidResponse;
}

//get only pending bids
Response<QVector<Bid>> Bid::GetPending()
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

//get only rejected bids that belong to a specific userID
Response<QVector<Bid>> Bid::GetRejected(int UserID)
{
    Response <QVector<Bid>> response = Bid::SearchByUserID(UserID);
    QVector<Bid> rejected;
    for(auto& b : response.Data)
    {
        if(b.EBS == 2) //if rejected
        {
            rejected.push_back(b);
        }
    }
    response.Data = rejected;
    return response;
}

//gets a list of bids that belong to a specific userID
Response<QVector<Bid>> Bid::SearchByUserID(int userID)
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

//gets a list of bids that are associated with a specific slotID
Response<QVector<Bid> > Bid::SearchBySlotID(int slotID)
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


//delete a bid by bidID
Response<void> Bid::Delete(int bidID)
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

//get users who have a bid for a specific bidID
Response<User> Bid::GetUserByBidID(int bidid)
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
            qDebug() <<"LongLong:" <<  userQuery.value("MaxSlots").toLongLong();
            qDebug() <<"Int:" <<  userQuery.value("MaxSlots").toInt();

            qDebug() <<"Entity Max Slots:" << user.MaxSlots;
            response.Data = user;
            response.Result = EDatabaseResult::EDR_SUCCESS;
            return response;
        }
        else
        {
            qWarning() << "User query failed:" << userQuery.lastError().text();
            response.Result = EDatabaseResult::EDR_FAILURE;
            return response;
        }
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

//get users with approved workslots/bid for a specific slot
Response<QVector<int>> Bid::GetStaff(int slotID)
{
    Response<QVector<int>> response;

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
        qDebug() << "Error getting user IDs associated with bid SLOTID:" << query.lastError();
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!");
        errorMsgBox.setText("Could not get users associated with slot.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Returning the same response object here instead of creating a new one.
    }

    // Retrieve and set the data
    while(query.next())
    {
        int userId = query.value(0).toInt();
        response.Data.push_back(userId);
    }

    // Set any other response attributes if necessary
    return response;
}

//approve a bid by bidid
Response<void> Bid::ApproveBid(int bidid)
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

Response<void> Bid::UnapproveBid(int bidid)
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

Response<void> Bid::RejectBid(int bidid)
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

