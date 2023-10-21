#include "Enums.h"
#include "NewSlot.h"
#include "Slot.h"
#include "QApplicationGlobal.h"
#include "SlotDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <string>

QVector<Slot> SlotDataAccessObject::GetAllSlots()
{
    QVector<Slot> Slots;

    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    QSqlQuery query("SELECT * FROM Slot");
    while (query.next())
    {
        int id = query.value("SlotID").toInt();
        QDate date = QDate::fromString(query.value("SlotDate").toString());
        QTime startTime = QTime::fromString(query.value("SlotStart").toString());
        QTime endTime = QTime::fromString(query.value("SlotEnd").toString());
        int curChefs = query.value("CurChefs").toInt();
        int curCashiers = query.value("CurCashiers").toInt();
        int curWaiters = query.value("CurWaiters").toInt();

        Slot Slot(id, date, startTime, endTime, curChefs, curCashiers, curWaiters);
        Slots.push_back(Slot);
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
    return Slots;
}

QVector<Slot> SlotDataAccessObject::CreateSlot(Slot newSlot)
{
    QVector<Slot> existingSlots = GetAllSlots();

    if (newSlot.StartTime == newSlot.EndTime)
    {
        qDebug() << "Error: The work slot has no duration.";
        this->Result = EDatabaseResult::EDR_FAILURE;
        return existingSlots;
    }

    for (const Slot &existingSlot : existingSlots)
    {
        if (newSlot.HasOverlap(existingSlot))
        {
            qDebug() << "Error: The new work slot overlaps with an existing Slot.";
            this->Result = EDatabaseResult::EDR_FAILURE;
            return existingSlots;
        }
    }

    // If no overlaps found, insert the new Slot
    QSqlQuery query;
    query.prepare("INSERT INTO Slot (SlotDate, SlotStart, SlotEnd, CurChefs, CurCashiers, CurWaiters) "
                    "VALUES (:date, :start, :end, :curChefs, :curCashiers, :curWaiters)");
    query.bindValue(":date", newSlot.Date.toString());
    query.bindValue(":start", newSlot.StartTime.toString());
    query.bindValue(":end", newSlot.EndTime.toString());
    query.bindValue(":curChefs", newSlot.CurChefs);
    query.bindValue(":curCashiers", newSlot.CurCashiers);
    query.bindValue(":curWaiters", newSlot.CurWaiters);

    if (!query.exec())
    {
        qDebug() << "Error inserting Slot:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return existingSlots;
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
    return GetAllSlots();
}

QVector<Slot> SlotDataAccessObject::SearchDate(QDate date)
{
    QVector<Slot> Slots;

    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Slot WHERE SlotDate = :date"); // Prepare the query first
    query.bindValue(":date", date.toString());

    if (!query.exec()) {
        qWarning() << "Failed to execute Slot Search query:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return Slots;
    }

    while (query.next())
    {
        int id = query.value("SlotID").toInt();
        QDate date = QDate::fromString(query.value("SlotDate").toString());
        QTime startTime = QTime::fromString(query.value("SlotStart").toString());
        QTime endTime = QTime::fromString(query.value("SlotEnd").toString());
        int curChefs = query.value("CurChefs").toInt();
        int curCashiers = query.value("CurCashiers").toInt();
        int curWaiters = query.value("CurWaiters").toInt();

        Slot Slot(id, date, startTime, endTime, curChefs, curCashiers, curWaiters);
        Slots.push_back(Slot);
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
    return Slots;

}

std::vector<User> SlotDataAccessObject::GetUsersBySlotID(int SlotID)
{
    std::vector<User> users;

    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return users; // Return empty vector
    }

    QSqlQuery query;

    // First, get the UserIDs from the UserSlot table
    query.prepare("SELECT UserID FROM UserSlot WHERE SlotID = ?");
    query.addBindValue("SlotID");
    if (!query.exec()) {
        qWarning() << "Failed to execute UserSlot query:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return users;
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

            users.push_back(user);
        }
        else
        {
            qWarning() << "Failed to execute User query or user not found:" << userQuery.lastError();
            this->Result = EDatabaseResult::EDR_FAILURE;

        }
    }
    this->Result = EDatabaseResult::EDR_SUCCESS;
    return users;
}

void SlotDataAccessObject::DeleteSlot(int SlotID)
{
    if (!DATABASE.open())
    {
        qDebug() << "Error: Unable to open the database.";
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    QSqlQuery query;

    // Prepare SQL statement to delete user with the given username
    query.prepare("DELETE FROM Slot WHERE SlotID = :slotid");

    query.bindValue(":slotid", SlotID);

    if (!query.exec())
    {
        qDebug() << "Error: Failed to delete user. Error:" << query.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return;
    }

    if (query.numRowsAffected() == 0)
    {
        qDebug() << "No workslot found with the slotID.";
        this->Result = EDatabaseResult::EDR_FAILURE;
        return;
    }
    else
    {
        this->Result = EDatabaseResult::EDR_SUCCESS;
    }
}

QVector<Slot> SlotDataAccessObject::UpdateSlot(Slot editedSlot)
{
    QVector<Slot> existingSlots = this->GetAllSlots();

    if (editedSlot.StartTime == editedSlot.EndTime)
    {
        qDebug() << "Error: The work slot has no duration.";
        this->Result = EDatabaseResult::EDR_FAILURE;
        return existingSlots;
    }

    for (const Slot &existingSlot : existingSlots)
    {
        if (editedSlot.HasOverlap(existingSlot) && editedSlot.SlotID != existingSlot.SlotID)
        {
            qDebug() << "Error: The new work slot overlaps with an existing Slot.";
            this->Result = EDatabaseResult::EDR_FAILURE;
            return existingSlots;
        }
    }


    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // slot exists, proceed with update
    QSqlQuery query;
    query.prepare("UPDATE Slot SET SlotDate = :date, SlotStart = :start, SlotEnd = :end, CurChefs = :curChefs, CurCashiers = :curCashiers, CurWaiters = :curWaiters WHERE SlotID = :slotid");
    query.bindValue(":slotid", editedSlot.SlotID);
    query.bindValue(":date", editedSlot.Date.toString());
    query.bindValue(":start", editedSlot.StartTime.toString());
    query.bindValue(":end", editedSlot.EndTime.toString());
    query.bindValue(":curChefs", editedSlot.CurChefs);
    query.bindValue(":curCashiers", editedSlot.CurCashiers);
    query.bindValue(":curWaiters", editedSlot.CurWaiters);

    if (query.exec())
    {
        qDebug() << "Update slot succeded.";
        this->Result = EDatabaseResult::EDR_SUCCESS;
        return this->GetAllSlots();
    }
    else
    {
        qWarning() << "Update slot failed: " << query.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return this->GetAllSlots();
    }

}
