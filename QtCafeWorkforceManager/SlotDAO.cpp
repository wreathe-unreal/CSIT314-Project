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
        QDate date = QDate::fromString(query.value("SlotDate").toString(), "yyyy-MM-dd");
        QTime startTime = QTime::fromString(query.value("SlotStart").toString(), "hh:mm:ss");
        QTime endTime = QTime::fromString(query.value("SlotEnd").toString(), "hh:mm:ss");
        int maxChefs = query.value("MaxChefs").toInt();
        int curChefs = query.value("CurChefs").toInt();
        int maxCashiers = query.value("MaxCashiers").toInt();
        int curCashiers = query.value("CurCashiers").toInt();
        int maxWaiters = query.value("MaxWaiters").toInt();
        int curWaiters = query.value("CurWaiters").toInt();

        Slot Slot(id, date, startTime, endTime, maxChefs, curChefs, maxCashiers, curCashiers, maxWaiters, curWaiters);
        Slots.push_back(Slot);
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
    return Slots;
}

void SlotDataAccessObject::InsertSlot(NewSlot newSlot)
{
    QVector<Slot> existingSlots = GetAllSlots();
    for (const Slot &existingSlot : existingSlots)
    {
        if (newSlot.HasOverlap(existingSlot))
        {
            qDebug() << "Error: The new Slot overlaps with an existing Slot.";
            this->Result = EDatabaseResult::EDR_FAILURE;
        }
    }

    // If no overlaps found, insert the new Slot
    QSqlQuery query;
    query.prepare("INSERT INTO Slot (SlotDate, SlotStart, SlotEnd, MaxChefs, CurChefs, MaxCashiers, CurCashiers, MaxWaiters, CurWaiters) "
                  "VALUES (:date, :start, :end, :maxChefs, :curChefs, :maxCashiers, :curCashiers, :maxWaiters, :curWaiters)");
    query.bindValue(":date", newSlot.Date.toString("yyyy-MM-dd"));
    query.bindValue(":start", newSlot.StartTime.toString("hh:mm:ss"));
    query.bindValue(":end", newSlot.EndTime.toString("hh:mm:ss"));
    query.bindValue(":maxChefs", newSlot.MaxChefs);
    query.bindValue(":curChefs", newSlot.CurChefs);
    query.bindValue(":maxCashiers", newSlot.MaxCashiers);
    query.bindValue(":curCashiers", newSlot.CurCashiers);
    query.bindValue(":maxWaiters", newSlot.MaxWaiters);
    query.bindValue(":curWaiters", newSlot.CurWaiters);

    if (!query.exec())
    {
        qDebug() << "Error inserting Slot:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
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
