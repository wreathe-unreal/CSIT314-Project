#pragma once

#include "Bid.h"
#include "Enums.h"
#include "Slot.h"
#include "User.h"
#include <QString>
#include <QVector>
#include "Response.h"

class IController
{
    public:
    IController(){};
   ~IController(){};
};

class AuthorizeController : public IController
{
   public:
    QString Username;
    QString Password;

   AuthorizeController(QString username, QString password)
   {
       this->Username = username;
       this->Password = password;
   }

   Response<EUserProfile> Execute();

};


class GetUsersController : public IController
{
    public:
   Response<QVector<User>> Execute();
};

class UpdateUserController : public IController
{
    public:
        QString UsernameBeforeUpdate;
       User UpdatedUser;

       UpdateUserController(User updatedUser, QString usernameBeforeUpdate)
       {
            this->UpdatedUser = updatedUser;
            this->UsernameBeforeUpdate = usernameBeforeUpdate;
       }


       Response<void> Execute();
};

class CreateUserController : public IController
{
   public:
       User NewUser;

       CreateUserController(User newUser)
       {
            this->NewUser = newUser;
       }


       Response<void> Execute();
};

class DeleteUserController : public IController
{
   public:
       QString UsernameToDelete;

       DeleteUserController(QString usernameToDelete)
       {
            this->UsernameToDelete = usernameToDelete;
       }

       Response<void> Execute();
};

class SearchByEUPController : public IController
{
   public:
       EUserProfile profile;

       SearchByEUPController(EUserProfile userProfile)
       {
            this->profile = userProfile;
       }

       Response<QVector<User>> Execute();
};


class CreateSlotController: public IController
{
   public:
       Slot NewSlot;
       CreateSlotController(Slot newslot)
       {
            this->NewSlot = newslot;
       }

       Response<QVector<Slot>> Execute();
};

class GetSlotsController: public IController
{
   public:
       Response<QVector<Slot>> Execute();
};

class DeleteSlotController: public IController
{
    public:
        int SlotID;
        DeleteSlotController(int slotID)
        {
            this->SlotID = slotID;
        }
        Response<void> Execute();
};

class UpdateSlotController: public IController
{
    public:
        Slot SlotToEdit;
        UpdateSlotController(Slot slotToEdit)
        {
            this->SlotToEdit = slotToEdit;
        }

        Response<QVector<Slot>> Execute();
};

class SearchSlotByDayController : public IController
{
    public:
        QDate Date;
        SearchSlotByDayController(QDate date)
        {
            this->Date = date;
        }
        Response<QVector<Slot>> Execute();
};


class SearchSlotsByUserIDController : public IController
{
    public:
        int UserID;
        SearchSlotsByUserIDController(int userID)
        {
            this->UserID = userID;
        }
        Response<QVector<Slot>> Execute();
};


class SetESRController : public IController
{
    public:
        QString Username;
        EStaffRole NewESR;

        SetESRController(QString username, EStaffRole newESR)
        {
            this->Username = username;
            this->NewESR = newESR;
        }
        Response<void> Execute();
};

class SetNameController : public IController
{
    public:
        QString Username;
        QString NewName;
        SetNameController(QString username, QString newName)
        {
            this->Username = username;
            this->NewName = newName;
        }

        Response<void> Execute();
};

class SetMaxSlotsController : public IController
{
    public:
        QString Username;
        int MaxSlots;
        SetMaxSlotsController(QString username, int maxSlots)
        {
            this->Username = username;
            this->MaxSlots = maxSlots;
        }

        Response<void> Execute();
};

class GetUserController : public IController
{
    public:
        QString Username;
        int UserID;

        GetUserController(QString username)
        {
            this->UserID = -1;
            this->Username = username;
        }

        GetUserController(int userID)
        {
            this->UserID = userID;
            this->Username = "";
        }

        Response<User> Execute();
};

class InsertBidController : public IController
{
    public:
        Bid NewBid;
        InsertBidController(Bid newBid)
        {
            this->NewBid = newBid;
        }
        Response<void> Execute();
};

class GetPendingBidsController : public IController
{
    public:
        GetPendingBidsController()
        {

        }
        Response<QVector<Bid>> Execute();
};

class GetSlotController : public IController
{
    public:
        int SlotID;
        GetSlotController(int slotID)
        {
            this->SlotID = slotID;
        }
        Response<Slot> Execute();
};

class SearchBidsByUserIDController : public IController
{
    public:
        int UserID;
        SearchBidsByUserIDController(int userID)
        {
            this->UserID = userID;
        }
        Response<QVector<Bid>> Execute();
};

class DeleteBidController : public IController
{
    public:
        int BidID;
        DeleteBidController(int bidID)
        {
            this->BidID = bidID;
        }
        Response<void> Execute();
};

class SearchBidsBySlotIDController : public IController
{
    public:
        int SlotID;
        SearchBidsBySlotIDController(int slotID)
        {
            this->SlotID = slotID;
        }
        Response<QVector<Bid>> Execute();
};

class SearchWorkersBySlotIDController : public IController
{
    public:
        int SlotID;
        SearchWorkersBySlotIDController(int slotid)
        {
            this->SlotID = slotid;
        }
        Response<QVector<User>> Execute();
};

class GetUserByBidIDController : public IController
{
    public:
        int BidID;
        GetUserByBidIDController(int bidID)
        {
            this->BidID = bidID;
        }
        Response<User> Execute();
};

class ApproveBidController : public IController
{
    public:
        int BidID;
        ApproveBidController(int bidid)
        {
            this->BidID = bidid;
        }
        Response<void> Execute();
};

class GetBidController : public IController
{
    public:
        int BidID;
        GetBidController(int bidid)
        {
            this->BidID = bidid;
        }
        Response<Bid> Execute();
};

class GetApprovedUsersBySlotController : public IController
{
    public:
        int SlotID;
        GetApprovedUsersBySlotController(int slotID)
        {
            this->SlotID = slotID;
        }
        Response<QVector<User>> Execute();
};

class GetBiddersBySlotIDController : public IController
{
    public:
        int SlotID;
        GetBiddersBySlotIDController(int slotID)
        {
            this->SlotID = slotID;
        }
        Response<QVector<User>> Execute();
};

class UnapproveBidController : public IController
{
    public:
        int BidID;
        UnapproveBidController(int bidID)
        {
            this->BidID = bidID;
        }
        Response<void> Execute();
};

class RejectBidController : public IController
{
    public:
        int BidID;
        RejectBidController(int bidID)
        {
            this->BidID = bidID;
        }
        Response<void> Execute();
};

class GetUserRejectedBidsController : public IController
{
    public:
        int UserID;
        GetUserRejectedBidsController(int userID)
        {
            this->UserID = userID;
        }

        Response<QVector<Bid>> Execute();
};
