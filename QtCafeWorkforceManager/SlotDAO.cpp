#include "Enums.h"
#include "NewSlot.h"
#include "Slot.h"
#include "QApplicationGlobal.h"
#include "SlotDAO.h"
#include <QSqlQuery>
#include "Response.h"
#include <QSqlError>
#include <string>

QVector<Slot> SlotDataAccessObject::GetAllSlots()
{
    QVector<Slot> Slots;
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

    return Slots;
}

ECommandResult SlotDataAccessObject::InsertSlot(NewSlot newSlot)
{
    QVector<Slot> existingSlots = GetAllSlots();
    for (const Slot &existingSlot : existingSlots)
    {
        if (newSlot.HasOverlap(existingSlot))
        {
            qDebug() << "Error: The new Slot overlaps with an existing Slot.";
            return ECommandResult::ECR_FAILURE;
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
        return ECommandResult::ECR_FAILURE;
    }

    return ECommandResult::ECR_SUCCESS;
}
