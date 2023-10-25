#pragma once

#include "Bid.h"
#include "Enums.h"
#include "Slot.h"
#include "User.h"
#include <QString>

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
       Username = username;
       Password = password;
   }

   EUserProfile Execute();

};


class GetUsersController : public IController
{
    public:
        QVector<User> Execute();
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


       void Execute();
};

class CreateUserController : public IController
{
   public:
       User NewUser;

       CreateUserController(User newUser)
       {
            this->NewUser = newUser;
       }


       void Execute();
};

class DeleteUserController : public IController
{
   public:
       QString UsernameToDelete;

       DeleteUserController(QString usernameToDelete)
       {
            this->UsernameToDelete = usernameToDelete;
       }

       void Execute();
};

class SearchByEUPController : public IController
{
   public:
       EUserProfile profile;

       SearchByEUPController(EUserProfile userProfile)
       {
            this->profile = userProfile;
       }

       QVector<User> Execute();
};


class CreateSlotController: public IController
{
   public:
       Slot NewSlot;
       CreateSlotController(Slot newslot)
       {
            this->NewSlot = newslot;
       }

       QVector<Slot> Execute();
};

class GetSlotsController: public IController
{
   public:
    QVector<Slot> Execute();
};

class DeleteSlotController: public IController
{
    public:
        int SlotID;
        DeleteSlotController(int slotID)
        {
            this->SlotID = slotID;
        }
        void Execute();
};

class UpdateSlotController: public IController
{
    public:
        Slot SlotToEdit;
        UpdateSlotController(Slot slotToEdit)
        {
            this->SlotToEdit = slotToEdit;
        }

        QVector<Slot> Execute();
};

class SearchSlotByDayController : public IController
{
    public:
        QDate Date;
        SearchSlotByDayController(QDate date)
        {
            this->Date = date;
        }
        QVector<Slot> Execute();
};

class IsUserActiveController : public IController
{
    public:
        QString Username;
        IsUserActiveController(QString username)
        {
            this->Username = username;
        }
        void Execute();
};

class GetUserIDController : public IController
{
    public:
        QString Username;
        GetUserIDController(QString username)
        {
            this->Username = username;
        }
        int Execute();
};

class SearchSlotsByUserIDController : public IController
{
    public:
        int UserID;
        SearchSlotsByUserIDController(int userID)
        {
            this->UserID = userID;
        }
        QVector<Slot> Execute();
};

class GetEUPController : public IController
{
    public:
        QString Username;

        GetEUPController(QString username)
        {
            this->Username = username;
        }
        EUserProfile Execute();

};


class GetESRController : public IController

{
    public:
        QString Username;

        GetESRController(QString username)
        {
            this->Username = username;
        }
        EStaffRole Execute();
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
        void Execute();
};

class GetNameController : public IController
{
    public:
        QString Username;
        GetNameController(QString username)
        {
            this->Username = username;
        }
        QString Execute();
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

        void Execute();
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

        void Execute();
};

class GetUserController : public IController
{
    public:
        QString Username;

        GetUserController(QString username)
        {
            this->Username = username;
        }

        User Execute();
};

class GetBidDAOResult : public IController
{
    public:
        GetBidDAOResult()
        {

        }

        EDatabaseResult Execute();
};

class GetUserDAOResult : public IController
{
    public:
        GetUserDAOResult()
        {

        }

        EDatabaseResult Execute();
};

class GetSlotDAOResult : public IController
{
    public:
        GetSlotDAOResult()
        {

        }

        EDatabaseResult Execute();
};

class ResetUserDAOResult : public IController
{
    public:
        ResetUserDAOResult()
        {

        }
        void Execute();
};

class ResetSlotDAOResult : public IController
{
    public:
        ResetSlotDAOResult()
        {

        }
        void Execute();
};

class ResetBidDAOResult : public IController
{
    public:
        ResetBidDAOResult()
        {

        }
        void Execute();
};

class InsertBidController : public IController
{
    public:
        Bid NewBid;
        InsertBidController(Bid newBid)
        {
            this->NewBid = newBid;
        }
        void Execute();
};

class GetPendingBidsController : public IController
{
    public:
        GetPendingBidsController()
        {

        }
        QVector<Bid> Execute();
};

class GetSlotController : public IController
{
    public:
        int SlotID;
        GetSlotController(int slotID)
        {
            this->SlotID = slotID;
        }
        Slot Execute();
};

class SearchBidsByUserIDController : public IController
{
    public:
        int UserID;
        SearchBidsByUserIDController(int userID)
        {
            this->UserID = userID;
        }
        QVector<Bid> Execute();
};
