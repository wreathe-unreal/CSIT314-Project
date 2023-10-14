// Shift.h
#ifndef SHIFT_H
#define SHIFT_H
#include "Entity.h"
#include <QDate>

class Shift : public IEntity
{

    public:
        Shift();
        ~Shift();

        int getShiftID() const;

        QDate getShiftDate() const;
        void setShiftDate(const QDate &newShiftDate);

        int getMaxChefs() const;

        int getCurChefs() const;
        void setCurChefs(int newCurChefs);

        int getCurCashiers() const;
        void setCurCashiers(int newCurCashiers);

        int getMaxCashiers() const;

        int getCurWaiters() const;
        void setCurWaiters(int newCurWaiters);

        int getMaxWaiters() const;

        bool isChefRoleFull() const;
        bool isCashierRoleFull() const;
        bool isWaiterRoleFull() const;
        bool isShiftFull() const;

        QTime getStartTime() const;

        QTime getEndTime() const;


        bool HasOverlap(Shift otherShift)
        {
            return RangeContainsStartInclusive(this->StartTime, this->EndTime, otherShift.StartTime)
                || RangeContainsEndInclusive(this->StartTime, this->EndTime, otherShift.EndTime)
                || RangeContainsStartInclusive(otherShift.StartTime, otherShift.EndTime, this->StartTime)
                || RangeContainsEndInclusive(otherShift.StartTime, otherShift.EndTime, this->EndTime);
        }

        virtual void ToString() override { qDebug() << getShiftID();}

    private:
        int ShiftID;
        QDate Date;
        QTime StartTime;
        QTime EndTime;
        int MaxChefs;
        int CurChefs;
        int MaxCashiers;
        int CurCashiers;
        int MaxWaiters;
        int CurWaiters;

        Shift(QDate date, QTime startTime, QTime endTime) { this->Date = date; this->StartTime = startTime; this->EndTime = endTime;}

        bool RangeContainsEndInclusive(QTime start, QTime end, QTime value)
        {
            if(value > start && value <= end)
            {
                return true;
            }
            return false;
        }

        bool RangeContainsStartInclusive(QTime start, QTime end, QTime value)
        {
            if(value >= start && value < end)
            {
                return true;
            }
            return false;
        }
};

#endif // SHIFT_H
