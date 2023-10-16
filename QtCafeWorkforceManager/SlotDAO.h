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
        SlotDataAccessObject(){};
        ~SlotDataAccessObject(){};

        //uncoded
        QVector<Slot> GetAllSlots();
        ECommandResult InsertSlot(NewSlot newSlot);
        ECommandResult AssignStaff(Slot slot, User user);
        Slot GetSlot(Slot slot);
        std::vector<User> GetStaff(Slot slot);
        std::vector<User> GetUnassignedStaff(Slot slot);
        std::vector<User> GetBidders(Slot slot);
        std::vector<Slot> GetByDate(QDate date);
        std::vector<Slot> GetByUser(std::string username);
        std::vector<User> GetUsersBySlotID(int SlotID);

};

#endif // SLOTDAO_H
