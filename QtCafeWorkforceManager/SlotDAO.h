#ifndef SLOTDAO_H
#define SLOTDAO_H
#include "Enums.h"
#include "NewSlot.h"
#include "Response.h"
#include "Slot.h"
#include "User.h"

#define DATABASE QApplicationGlobal::CafeDB

class SlotDataAccessObject
{
    public:
    SlotDataAccessObject(){};
    ~SlotDataAccessObject(){};

    //uncoded
    Response<QVector<Slot>> GetAllSlots();
    Response<QVector<Slot>> CreateSlot(Slot newSlot);
    Response<void> AssignStaff(Slot slot, User user);
    Response<Slot> GetSlot(int slotID);
    Response<QVector<User>> GetStaff(int SlotID);
    Response<QVector<User>> GetUnassignedStaff(Slot slot);
    Response<QVector<User>> GetBidders(Slot slot);
    Response<QVector<Slot>> SearchDate(QDate date);
    Response<QVector<User>> GetUsersBySlotID(int SlotID);
    Response<void> DeleteSlot(int SlotID);
    Response<QVector<Slot>> UpdateSlot(Slot editedSlot);
    Response<QVector<Slot>> SearchByUserID(int userID);

};

#endif // SLOTDAO_H
