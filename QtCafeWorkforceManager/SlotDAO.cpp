#include "Enums.h"
#include "Slot.h"
#include "QApplicationGlobal.h"
#include "SlotDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include "Response.h"
#include <QMessageBox>

Response<QVector<Slot>> SlotDataAccessObject::GetAllSlots()
{
    Response<QVector<Slot>> response;

    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query("SELECT * FROM Slot");
    while (query.next())
    {
        int id = query.value("SlotID").toInt();
        QDate date = QDate::fromString(query.value("SlotDate").toString());
        QTime startTime = QTime::fromString(query.value("SlotStart").toString());
        QTime endTime = QTime::fromString(query.value("SlotEnd").toString());

        Slot Slot(id, date, startTime, endTime);
        response.Data.push_back(Slot);
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<QVector<Slot>> SlotDataAccessObject::CreateSlot(Slot newSlot)
{
    Response<QVector<Slot>> response = GetAllSlots();

    if(response.Result != EDatabaseResult::EDR_SUCCESS)
    {
        qDebug() << "Error: Could not get slots.";
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("Could not build workslot array."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();

        response.Result = EDatabaseResult::EDR_FAILURE;
        response.Data.empty();
        return response;
    }

    QVector<Slot> existingSlots = response.Data;
    response = Response<QVector<Slot>>(); //reset response

    if (newSlot.StartTime >= newSlot.EndTime)
    {
        qDebug() << "Error: The work slot has no duration.";
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("The work slot has no duration."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();

        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    for (const Slot &existingSlot : existingSlots)
    {
        if (newSlot.HasOverlap(existingSlot))
        {
            QMessageBox errorMsgBox;
            errorMsgBox.setWindowTitle("Error!"); // Set the window title
            errorMsgBox.setText("The work slot overlaps with an existing work slot."); // Set the text to display
            errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

            // Show the message box as a modal dialog
            errorMsgBox.exec();
            qDebug() << "Error: The new work slot overlaps with an existing Slot.";
            response.Result = EDatabaseResult::EDR_FAILURE;
            return response;
        }
    }

    // If no overlaps found, insert the new Slot
    QSqlQuery query;
    query.prepare("INSERT INTO Slot (SlotDate, SlotStart, SlotEnd) "
                    "VALUES (:date, :start, :end)");
    query.bindValue(":date", newSlot.Date.toString());
    query.bindValue(":start", newSlot.StartTime.toString());
    query.bindValue(":end", newSlot.EndTime.toString());

    if (!query.exec())
    {
        qDebug() << "Error inserting Slot:" << query.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;

    return GetAllSlots();
}

Response<Slot> SlotDataAccessObject::GetSlot(int slotID)
{
    Response<Slot> response;

    // Check if the database is connected
    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Return default slot if database connection fails
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Slot WHERE SlotID = :slotID");
    query.bindValue(":slotID", slotID);

    // Check if the query was executed correctly
    if (!query.exec()) {
        qDebug() << "Error inserting Slot:" << query.lastError();
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!");
        errorMsgBox.setText("Could not get slot.");
        errorMsgBox.setIcon(QMessageBox::Critical);
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    // If a slot with the given SlotID is found, extract its details
    if (query.next())
    {
        int id = query.value("SlotID").toInt();
        QDate date = QDate::fromString(query.value("SlotDate").toString());
        QTime startTime = QTime::fromString(query.value("SlotStart").toString());
        QTime endTime = QTime::fromString(query.value("SlotEnd").toString());

        Slot slot(id, date, startTime, endTime);
        response.Result = EDatabaseResult::EDR_SUCCESS;
        response.Data = slot;
        return response;
    }
    else
    {
        // If no slot with the given SlotID is found, log a message and return a default Slot
        qDebug() << "No Slot found for SlotID:" << slotID;
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }
    response.Result = EDatabaseResult::EDR_FAILURE;
    return response;
}

Response<QVector<Slot>> SlotDataAccessObject::SearchDate(QDate date)
{
    Response<QVector<Slot>> response;

    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Slot WHERE SlotDate = :date"); // Prepare the query first
    query.bindValue(":date", date.toString());

    if (!query.exec()) {
        qWarning() << "Failed to execute Slot Search query:" << query.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    while (query.next())
    {
        int id = query.value("SlotID").toInt();
        QDate date = QDate::fromString(query.value("SlotDate").toString());
        QTime startTime = QTime::fromString(query.value("SlotStart").toString());
        QTime endTime = QTime::fromString(query.value("SlotEnd").toString());

        Slot Slot(id, date, startTime, endTime);
        response.Data.push_back(Slot);
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;

}

Response<QVector<User>> SlotDataAccessObject::GetUsersBySlotID(int SlotID)
{
    Response<QVector<User>> response;

    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query;

    // Get the UserIDs from the Bid table for the given SlotID
    query.prepare("SELECT UserID FROM Bid WHERE SlotID = ?");
    query.addBindValue(SlotID);
    if (!query.exec()) {
        qWarning() << "Failed to execute Bid query:" << query.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    while (query.next()) {
        int userID = query.value(0).toInt();

        // Then, for each UserID, get the User details from the User table
        QSqlQuery userQuery;
        userQuery.prepare("SELECT * FROM User WHERE UserID = ?");
        userQuery.addBindValue(userID);
        if (userQuery.exec() && userQuery.next())
        {
            User user;
            user.setUsername(userQuery.value("Username").toString());
            user.setPassword(userQuery.value("Password").toString());
            user.setEUP(userQuery.value("EUP").toInt());
            user.setESR(userQuery.value("ESR").toInt());
            user.setMaxSlots(userQuery.value("MaxSlots").toInt());

            response.Data.push_back(user);
        }
        else
        {
            qWarning() << "Failed to execute User query or user not found:" << userQuery.lastError();
            response.Result = EDatabaseResult::EDR_FAILURE;
            return response;
        }
    }
    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<void> SlotDataAccessObject::DeleteSlot(int SlotID)
{
    Response<void> response;

    if (!DATABASE.open())
    {
        qDebug() << "Error: Unable to open the database.";
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query;

    // Prepare SQL statement to delete user with the given username
    query.prepare("DELETE FROM Slot WHERE SlotID = :slotid");

    query.bindValue(":slotid", SlotID);

    if (!query.exec())
    {
        qDebug() << "Error: Failed to delete user. Error:" << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    if (query.numRowsAffected() == 0)
    {
        qDebug() << "No workslot found with the slotID.";
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }
    else
    {
        response.Result = EDatabaseResult::EDR_SUCCESS;
        return response;
    }
}

Response<QVector<Slot>> SlotDataAccessObject::UpdateSlot(Slot editedSlot)
{
    Response<QVector<Slot>> response = GetAllSlots();

    if (editedSlot.StartTime == editedSlot.EndTime)
    {
        qDebug() << "Error: The work slot has no duration.";
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("The work slot has no duration."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
        response.Result = EDatabaseResult::EDR_FAILURE;
        response.Data.empty();
        return response;
    }

    QVector<Slot> existingSlots = response.Data;
    response = Response<QVector<Slot>>(); //reset response

    for (const Slot &existingSlot : existingSlots)
    {
        if (editedSlot.HasOverlap(existingSlot) && editedSlot.SlotID != existingSlot.SlotID)
        {
            qDebug() << "Error: The new work slot overlaps with an existing Slot.";
            QMessageBox errorMsgBox;
            errorMsgBox.setWindowTitle("Error!"); // Set the window title
            errorMsgBox.setText("The work slot overlaps with an existing work slot."); // Set the text to display
            errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

            // Show the message box as a modal dialog
            errorMsgBox.exec();
            response.Result = EDatabaseResult::EDR_FAILURE;
            return response;
        }
    }


    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    // slot exists, proceed with update
    QSqlQuery query;
    query.prepare("UPDATE Slot SET SlotDate = :date, SlotStart = :start, SlotEnd = :end WHERE SlotID = :slotid");
    query.bindValue(":slotid", editedSlot.SlotID);
    query.bindValue(":date", editedSlot.Date.toString());
    query.bindValue(":start", editedSlot.StartTime.toString());
    query.bindValue(":end", editedSlot.EndTime.toString());
    if (query.exec())
    {
        qDebug() << "Update slot succeded.";            qDebug() << "Error: The new work slot overlaps with an existing Slot.";
        QMessageBox updateMsgBox;
        updateMsgBox.setWindowTitle("Slot Updated!"); // Set the window title
        updateMsgBox.setText("The work slot has been updated."); // Set the text to display
        updateMsgBox.setIcon(QMessageBox::Information); // Set an icon for the message box

        // Show the message box as a modal dialog
        updateMsgBox.exec();
        response = GetAllSlots();
        return response;
    }
    else
    {
        qWarning() << "Update slot failed: " << query.lastError().text();
        qDebug() << "Error: The new work slot overlaps with an existing Slot.";
        QMessageBox errorMsgBox;
        errorMsgBox.setWindowTitle("Error!"); // Set the window title
        errorMsgBox.setText("The work slot overlaps with an existing work slot."); // Set the text to display
        errorMsgBox.setIcon(QMessageBox::Critical); // Set an icon for the message box

        // Show the message box as a modal dialog
        errorMsgBox.exec();
        return GetAllSlots();
    }

}

Response<QVector<Slot>> SlotDataAccessObject::SearchByUserID(int userID)
{
    Response<QVector<Slot>> response;

    if (!DATABASE.isOpen())
    {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    // Updated query to get SlotID from Bid table where EBS is 1 (approved bid) for the given userID
    QSqlQuery query("SELECT SlotID FROM Bid WHERE UserID = ? AND EBS = 1");
    query.addBindValue(userID);

    // Error checking after query execution
    if(!query.exec())
    {
        qDebug() << query.lastQuery();
        qWarning() << "Database query error:" << query.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;  // return the empty QVector or handle the error as appropriate
    }

    QVector<int> slotIDs;
    while (query.next())
    {
        slotIDs.push_back(query.value("SlotID").toInt());
    }

    // For each slotID, use GetSlot(int slotID) to get the Slot details and append it to the response Data.
    for (int slotID : slotIDs)
    {
        Response<Slot> slotResponse = GetSlotController(slotID).Execute();

        if (slotResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
            response.Data.push_back(slotResponse.Data);
        }
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}
