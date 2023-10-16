// NewSlot.h
#ifndef NEWSLOT_H
#define NEWSLOT_H
#include "Slot.h"
#include <QDate>
#include <QTime>


inline bool RangeContainsEndInclusive(QTime start, QTime end, QTime value)
{
    if(value > start && value <= end)
    {
        return true;
    }
    return false;
}

inline bool RangeContainsStartInclusive(QTime start, QTime end, QTime value)
{
    if(value >= start && value < end)
    {
        return true;
    }
    return false;
}

class NewSlot : public IEntity
{

public:
    NewSlot();
    ~NewSlot();

    QDate Date;
    QTime StartTime;
    QTime EndTime;
    int MaxChefs;
    int CurChefs;
    int MaxCashiers;
    int CurCashiers;
    int MaxWaiters;
    int CurWaiters;

    NewSlot(QDate date, QTime startTime, QTime endTime, int maxChefs, int maxCashiers, int maxWaiters)
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

    bool HasOverlap(Slot otherSlot)
    {
        return RangeContainsStartInclusive(this->StartTime, this->EndTime, otherSlot.getStartTime())
               || RangeContainsEndInclusive(this->StartTime, this->EndTime, otherSlot.getEndTime())
               || RangeContainsStartInclusive(otherSlot.getStartTime(), otherSlot.getEndTime(), this->StartTime)
               || RangeContainsEndInclusive(otherSlot.getStartTime(), otherSlot.getEndTime(), this->EndTime);
    }

    virtual void ToString() override{ qDebug() << this->Date << " " << this->StartTime << " to " << this->EndTime;};
};

#endif // NEWSLOT_H
