#include "UnitTests.h"
#include "QApplicationGlobal.h"
#include "Controller.h"
#include "BidDAO.h"
#include "UserDAO.h"
#include "SlotDAO.h"
#include "Slot.h"
#include "User.h"
#include "Bid.h"
#include "Enums.h"
#include <QVector>

QVector<User> UnitTests::InjectUsers;
QVector<Slot> UnitTests::InjectSlots;
QVector<Bid>  UnitTests::InjectBids;

UnitTests::UnitTests()
{

}

bool UnitTests::Assert()
{
    Response<QVector<User>> userResponse = GetUsersController().Execute();
    if (userResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        qDebug() << "Assert: GetUsers failed.";
        return false;
    }
    qDebug() << "Assert: GetUsers succeeded.";
    InjectUsers = userResponse.Data;

    Response<QVector<Slot>> slotResponse = GetSlotsController().Execute();
    if (slotResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        qDebug() << "Assert: GetSlots failed.";
        return false;
    }
    qDebug() << "Assert: GetSlots succeeded.";
    InjectSlots = slotResponse.Data;

    Response<QVector<Bid>> bidResponse = GetBidsController().Execute();
    if (bidResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        qDebug() << "Assert: GetBids failed.";
        return false;
    }
    qDebug() << "Assert: GetBids suceeeded.";
    InjectBids = bidResponse.Data;

    //copy the bids we will inject later and first, delete them
    QVector<Bid> deleteBids = InjectBids;
    //we delete bids first since they have no dependencies, then slots, then users
    for(auto& bid : deleteBids)
    {
        if(DeleteBidController(bid.getBidID()).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: DeleteBid failed.";
            return false;
        }
    }
    qDebug() << "Assert: DeleteBid succeeded.";


    QVector<Slot> deleteSlots = InjectSlots;
    for(auto& slot : deleteSlots)
    {
        if(DeleteSlotController(slot.SlotID).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: DeleteSlot failed.";
            return false;
        }
    }
    qDebug() << "Assert: DeleteSlot succeeded.";


    QVector<User> deleteUsers = InjectUsers;
    for(auto& user : deleteUsers)
    {
        if(DeleteUserController(user.getUsername()).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: DeleteUser failed.";
            return false;
        }
    }
    qDebug() << "Assert: DeleteUser succeeded.";


    //now we inject/create
    for(auto& user : InjectUsers)
    {
        if(CreateUserController(user).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: CreateUser failed.";
            return false;
        }
    }
    qDebug() << "Assert: CreateUser succeeded.";


    for(auto& slot : InjectSlots)
    {
        if(CreateSlotController(slot).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: CreateSlot failed.";
            return false;
        }
    }
    qDebug() << "Assert: CreateSlot succeeded.";


    for(auto& bid : InjectBids)
    {
        if(InsertBidController(bid).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: InsertBid failed.";
            return false;
        }
    }
    qDebug() << "Assert: InsertBid succeeded.";


    //update users test
    int i = 1;
    for(auto& user : InjectUsers)
    {
        QString oldUsername = user.getUsername();
        user.setUsername("updateUsername" + QString::number(i));
        user.setPassword("updatedPassword");
        user.setEUP(3);
        user.setESR(3);
        user.setMaxSlots(100);
        if(UpdateUserController(user, oldUsername).Execute().Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: UpdateUser failed.";
            return false;
        }
        i++;
    }
    qDebug() << "Assert: UpdateUser succeeded.";


    // If all Execute functions returned a value other than EDR_Failure, return true
    return true;

}
