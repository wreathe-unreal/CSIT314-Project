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
        int getSlotID();

        QDate getDate();
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

        QTime getStartTime();
        void setStartTime(QTime time) { this->StartTime = time;}

        QTime getEndTime();
        void setEndTime(QTime time) { this->EndTime = time;}

        bool HasOverlap(Slot otherSlot)
        {
            if(this->Date != otherSlot.Date)
            {
                return false;
            }

            return (this->StartTime < otherSlot.EndTime) && (this->EndTime > otherSlot.StartTime);
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

};

#endif // SLOT_H
