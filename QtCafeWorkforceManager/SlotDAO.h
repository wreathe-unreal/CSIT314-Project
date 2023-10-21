#ifndef SLOTDAO_H
#define SLOTDAO_H
#include "Enums.h"
#include "NewSlot.h"
#include "Slot.h"
#include "User.h"

#define DATABASE QApplicationGlobal::CafeDB

class SlotDataAccessObject
{
    public:
    EDatabaseResult Result;
        SlotDataAccessObject(){};
        ~SlotDataAccessObject(){};

        //uncoded
        QVector<Slot> GetAllSlots();
        QVector<Slot> CreateSlot(Slot newSlot);
        void AssignStaff(Slot slot, User user);
        Slot GetSlot(Slot slot);
        std::vector<User> GetStaff(Slot slot);
        std::vector<User> GetUnassignedStaff(Slot slot);
        std::vector<User> GetBidders(Slot slot);
        QVector<Slot> SearchDate(QDate date);
        std::vector<Slot> GetByUser(std::string username);
        std::vector<User> GetUsersBySlotID(int SlotID);
        void DeleteSlot(int SlotID);
        QVector<Slot> UpdateSlot(Slot editedSlot);

};

#endif // SLOTDAO_H
