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

        int getCurChefs() const;
        void setCurChefs(int newCurChefs);

        int getCurCashiers() const;
        void setCurCashiers(int newCurCashiers);


        int getCurWaiters() const;
        void setCurWaiters(int newCurWaiters);

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
            if(this->Date != otherSlot.Date)
            {
                return false;
            }

            return RangeContainsStartInclusive(this->StartTime, this->EndTime, otherSlot.StartTime)
                ||  RangeContainsEndInclusive(this->StartTime, this->EndTime, otherSlot.EndTime)
                ||  RangeContainsStartInclusive(otherSlot.StartTime, otherSlot.EndTime, this->StartTime)
                ||  RangeContainsEndInclusive(otherSlot.StartTime, otherSlot.EndTime, this->EndTime);
        }

        virtual void ToString() override { qDebug() << getSlotID(); }

        //full constructor
        Slot(int ID, QDate date, QTime startTime, QTime endTime, int curChefs,int curCashiers, int curWaiters)
        {
            this->SlotID = ID;
            this->Date = date;
            this->StartTime = startTime;
            this->EndTime = endTime;
            this->CurChefs = curChefs;
            this->CurCashiers = curCashiers;
            this->CurWaiters = curWaiters;
        };

        //full constructor
        Slot(QDate date, QTime startTime, QTime endTime)
        {
            this->SlotID = 0;
            this->Date = date;
            this->StartTime = startTime;
            this->EndTime = endTime;
            this->CurChefs = 0;
            this->CurCashiers = 0;
            this->CurWaiters = 0;
        };

        int SlotID;
        QDate Date;
        QTime StartTime;
        QTime EndTime;
        int CurChefs;
        int CurCashiers;
        int CurWaiters;


    private:
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
