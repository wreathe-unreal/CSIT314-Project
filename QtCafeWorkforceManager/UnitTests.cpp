#include "UnitTests.h"
#include "Controller.h"
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
    Response<QVector<User>> userResponse = GetUsersController::Invoke();
    if (userResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        qDebug() << "Assert: GetUsers failed.";
        return false;
    }
    qDebug() << "Assert: GetUsers succeeded.";
    InjectUsers = userResponse.Data;

    for(auto u : InjectUsers)
    {
        if(AuthorizeController::Invoke(u.Username, u.Password).Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: AuthorizeUsers failed.";
            return false;
        }
        qDebug() << "Assert: AuthorizeUsers succeeded.";
    }

    if(AuthorizeController::Invoke("j32i42m3292i32", "239842kdm2idm3").Result == EDatabaseResult::EDR_FAILURE)
    {
        qDebug() << "Assert: UnauthorizedUserCannotLoginTest failed.";
        return false;
    }
    qDebug() << "Assert: UnauthorizedUserCannotLoginTest succeeded.";


    Response<QVector<Slot>> slotResponse = GetSlotsController::Invoke();
    if (slotResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        qDebug() << "Assert: GetSlots failed.";
        return false;
    }
    qDebug() << "Assert: GetSlots succeeded.";
    InjectSlots = slotResponse.Data;

    Response<QVector<Bid>> bidResponse = GetBidsController::Invoke();
    if (bidResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        qDebug() << "Assert: GetBids failed.";
        return false;
    }
    qDebug() << "Assert: GetBids suceeeded.";
    InjectBids = bidResponse.Data;

    QVector<User> deleteUsers = InjectUsers;
    for(auto& user : deleteUsers)
    {
        if(DeleteUserController::Invoke(user.UserID).Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: DeleteBids failed.";
            qDebug() << "Assert: DeleteUser failed.";
            return false;
        }
    }
    qDebug() << "Assert: DeleteBids succeeded.";
    qDebug() << "Assert: DeleteUser succeeded.";

    QVector<Bid> bids = GetBidsController::Invoke().Data;

    QVector<Slot> deleteSlots = InjectSlots;
    for(auto& slot : deleteSlots)
    {
        if(DeleteSlotController::Invoke(slot.SlotID).Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: DeleteSlot failed.";
            return false;
        }
    }
    qDebug() << "Assert: DeleteSlot succeeded.";

    //now we inject/create
    for(auto& user : InjectUsers)
    {
        if(CreateUserController::Invoke(user).Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: CreateUser failed.";
            return false;
        }
    }
    qDebug() << "Assert: CreateUser succeeded.";


    for(auto& slot : InjectSlots)
    {
        if(CreateSlotController::Invoke(slot).Result == EDatabaseResult::EDR_FAILURE)
        {
            qDebug() << "Assert: CreateSlot failed.";
            return false;
        }
    }
    qDebug() << "Assert: CreateSlot succeeded.";

    for(auto& bid : InjectBids)
    {
        if(CreateBidController::Invoke(bid).Result == EDatabaseResult::EDR_FAILURE)
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
        if(UpdateUserController::Invoke(user, oldUsername).Result == EDatabaseResult::EDR_FAILURE)
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
