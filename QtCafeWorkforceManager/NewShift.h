// NewShift.h
#ifndef NEWSHIFT_H
#define NEWSHIFT_H
#include "Shift.h"
#include <QDate>
#include <QTime>


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

class NewShift : public IEntity
{

public:
    NewShift();
    ~NewShift();

    QDate Date;
    QTime StartTime;
    QTime EndTime;
    int MaxChefs;
    int CurChefs;
    int MaxCashiers;
    int CurCashiers;
    int MaxWaiters;
    int CurWaiters;

    NewShift(QDate date, QTime startTime, QTime endTime, int maxChefs, int maxCashiers, int maxWaiters)
    {
        this->Date = date;
        this->StartTime = startTime;
        this->EndTime = endTime;
        this->MaxChefs = maxChefs;
        this->MaxCashiers = maxCashiers;
        this->MaxWaiters = maxWaiters;
        this->CurChefs = 0;
        this->CurCashiers = 0;
        this->CurWaiters = 0;
    }

    bool HasOverlap(Shift otherShift)
    {
        return RangeContainsStartInclusive(this->StartTime, this->EndTime, otherShift.getStartTime())
               || RangeContainsEndInclusive(this->StartTime, this->EndTime, otherShift.getEndTime())
               || RangeContainsStartInclusive(otherShift.getStartTime(), otherShift.getEndTime(), this->StartTime)
               || RangeContainsEndInclusive(otherShift.getStartTime(), otherShift.getEndTime(), this->EndTime);
    }

};

#endif // NEWSHIFT_H
