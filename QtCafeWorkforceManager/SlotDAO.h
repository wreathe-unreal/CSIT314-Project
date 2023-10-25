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
    SlotDataAccessObject()
    {
        Result = EDatabaseResult::EDR_UNINITIALIZED;
    };
    ~SlotDataAccessObject(){};

    //uncoded
    QVector<Slot> GetAllSlots();
    QVector<Slot> CreateSlot(Slot newSlot);
    void AssignStaff(Slot slot, User user);
    Slot GetSlot(int slotID);
    std::vector<User> GetStaff(Slot slot);
    std::vector<User> GetUnassignedStaff(Slot slot);
    std::vector<User> GetBidders(Slot slot);
    QVector<Slot> SearchDate(QDate date);
    std::vector<User> GetUsersBySlotID(int SlotID);
    void DeleteSlot(int SlotID);
    QVector<Slot> UpdateSlot(Slot editedSlot);
    QVector<Slot> SearchByUserID(int userID);

};

#endif // SLOTDAO_H
