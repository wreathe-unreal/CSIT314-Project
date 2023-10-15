#include "Enums.h"
#include "NewShift.h"
#include "Shift.h"
#include "QApplicationGlobal.h"
#include "ShiftDAO.h"
#include <QSqlQuery>
#include "Response.h"
#include <QSqlError>
#include <string>

QVector<Shift> ShiftDataAccessObject::GetAllShifts()
{
    QVector<Shift> shifts;
    QSqlQuery query("SELECT * FROM Shift");
    while (query.next())
    {
        int id = query.value("ShiftID").toInt();
        QDate date = QDate::fromString(query.value("ShiftDate").toString(), "yyyy-MM-dd");
        QTime startTime = QTime::fromString(query.value("ShiftStart").toString(), "hh:mm:ss");
        QTime endTime = QTime::fromString(query.value("ShiftEnd").toString(), "hh:mm:ss");
        int maxChefs = query.value("MaxChefs").toInt();
        int curChefs = query.value("CurChefs").toInt();
        int maxCashiers = query.value("MaxCashiers").toInt();
        int curCashiers = query.value("CurCashiers").toInt();
        int maxWaiters = query.value("MaxWaiters").toInt();
        int curWaiters = query.value("CurWaiters").toInt();

        Shift shift(id, date, startTime, endTime, maxChefs, curChefs, maxCashiers, curCashiers, maxWaiters, curWaiters);
        shifts.push_back(shift);
    }

    return shifts;
}

ECommandResult ShiftDataAccessObject::InsertShift(NewShift newShift)
{
    QVector<Shift> existingShifts = GetAllShifts();
    for (const Shift &existingShift : existingShifts)
    {
        if (newShift.HasOverlap(existingShift))
        {
            qDebug() << "Error: The new shift overlaps with an existing shift.";
            return ECommandResult::ECR_FAILURE;
        }
    }

    // If no overlaps found, insert the new shift
    QSqlQuery query;
    query.prepare("INSERT INTO Shift (ShiftDate, ShiftStart, ShiftEnd, MaxChefs, CurChefs, MaxCashiers, CurCashiers, MaxWaiters, CurWaiters) "
                  "VALUES (:date, :start, :end, :maxChefs, :curChefs, :maxCashiers, :curCashiers, :maxWaiters, :curWaiters)");
    query.bindValue(":date", newShift.Date.toString("yyyy-MM-dd"));
    query.bindValue(":start", newShift.StartTime.toString("hh:mm:ss"));
    query.bindValue(":end", newShift.EndTime.toString("hh:mm:ss"));
    query.bindValue(":maxChefs", newShift.MaxChefs);
    query.bindValue(":curChefs", newShift.CurChefs);
    query.bindValue(":maxCashiers", newShift.MaxCashiers);
    query.bindValue(":curCashiers", newShift.CurCashiers);
    query.bindValue(":maxWaiters", newShift.MaxWaiters);
    query.bindValue(":curWaiters", newShift.CurWaiters);

    if (!query.exec())
    {
        qDebug() << "Error inserting shift:" << query.lastError();
        return ECommandResult::ECR_FAILURE;
    }

    return ECommandResult::ECR_SUCCESS;
}
