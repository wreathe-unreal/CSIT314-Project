// Slot.h
#ifndef SLOT_H
#define SLOT_H
#include "Entity.h"
#include "Response.h"
#include <QDate>

class User;

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


        static Response<QVector<Slot>> GetAllSlots();
        static Response<QVector<Slot>> CreateSlot(Slot newSlot);
        static Response<void> AssignStaff(Slot slot, User user);
        static Response<Slot> GetSlot(int slotID);
        static Response<QVector<User>> GetStaff(int SlotID);
        static Response<QVector<User>> GetUnassignedStaff(Slot slot);
        static Response<QVector<User>> GetBidders(Slot slot);
        static Response<QVector<Slot>> SearchDate(QDate date);
        static Response<QVector<User>> GetUsersBySlotID(int SlotID);
        static Response<void> DeleteSlot(int SlotID);
        static Response<QVector<Slot>> UpdateSlot(Slot editedSlot);
        static Response<QVector<Slot>> SearchByUserID(int userID);


};

#endif // SLOT_H
