// Slot.h
#ifndef SLOT_H
#define SLOT_H
#include "Entity.h"
#include <QDate>

class Slot : public IEntity
{

    public:
        Slot(){};
        ~Slot(){};

        void setSlotID(int slotID);
        int getSlotID() const;

        QDate getDate() const;
        void setDate(QDate newSlotDate);

        void setMaxChefs(int maxChefs);
        int getMaxChefs() const;

        int getCurChefs() const;
        void setCurChefs(int newCurChefs);

        int getCurCashiers() const;
        void setCurCashiers(int newCurCashiers);

        int getMaxCashiers() const;
        void setMaxCashiers(int maxCashiers);

        int getCurWaiters() const;
        void setCurWaiters(int newCurWaiters);

        void setMaxWaiters(int maxWaiters);
        int getMaxWaiters() const;

        bool isChefRoleFull() const;
        bool isCashierRoleFull() const;
        bool isWaiterRoleFull() const;
        bool isSlotFull() const;

        QTime getStartTime() const;
        void setStartTime(QTime time) { this->StartTime = time;}

        QTime getEndTime() const;
        void setEndTime(QTime time) { this->EndTime = time;}

        bool HasOverlap(Slot otherSlot)
        {
            return (RangeContainsStartInclusive(this->StartTime, this->EndTime, otherSlot.StartTime)
                ||  RangeContainsEndInclusive(this->StartTime, this->EndTime, otherSlot.EndTime)
                ||  RangeContainsStartInclusive(otherSlot.StartTime, otherSlot.EndTime, this->StartTime)
                ||  RangeContainsEndInclusive(otherSlot.StartTime, otherSlot.EndTime, this->EndTime))
                &&  otherSlot.SlotID != this->SlotID;
        }

        virtual void ToString() override { qDebug() << getSlotID(); }

        //full constructor
        Slot(int ID, QDate date, QTime startTime, QTime endTime, int maxChefs, int curChefs, int  maxCashiers, int curCashiers, int  maxWaiters, int curWaiters)
        {
            this->SlotID = ID;
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
        int SlotID;
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

#endif // SLOT_H
