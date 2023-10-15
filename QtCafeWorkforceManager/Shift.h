// Shift.h
#ifndef SHIFT_H
#define SHIFT_H
#include "Entity.h"
#include <QDate>

class Shift : public IEntity
{

    public:
        Shift(){};
        ~Shift(){};

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
            return (RangeContainsStartInclusive(this->StartTime, this->EndTime, otherShift.StartTime)
                || RangeContainsEndInclusive(this->StartTime, this->EndTime, otherShift.EndTime)
                || RangeContainsStartInclusive(otherShift.StartTime, otherShift.EndTime, this->StartTime)
                || RangeContainsEndInclusive(otherShift.StartTime, otherShift.EndTime, this->EndTime))
                && otherShift.ShiftID != this->ShiftID;
        }

        virtual void ToString() override { qDebug() << getShiftID(); }

        //full constructor
        Shift(int ID, QDate date, QTime startTime, QTime endTime, int maxChefs, int curChefs, int  maxCashiers, int curCashiers, int  maxWaiters, int curWaiters)
        {
            this->ShiftID = ID;
            this->Date = date;
            this->StartTime = startTime;
            this->EndTime = endTime;
            this->MaxChefs = maxChefs;
            this->CurChefs = curChefs;
            this->MaxCashiers = maxCashiers;
            this->CurCashiers = curCashiers;
            this->MaxWaiters = maxWaiters;
            this->CurWaiters = curWaiters;
        };

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
