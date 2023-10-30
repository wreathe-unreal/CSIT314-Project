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
        Slot(int ID, QDate date, QTime startTime, QTime endTime)
        {
            this->SlotID = ID;
            this->Date = date;
            this->StartTime = startTime;
            this->EndTime = endTime;
        };

        //full constructor
        Slot(QDate date, QTime startTime, QTime endTime)
        {
            this->SlotID = 0;
            this->Date = date;
            this->StartTime = startTime;
            this->EndTime = endTime;
        };

        int SlotID;
        QDate Date;
        QTime StartTime;
        QTime EndTime;

};

#endif // SLOT_H
