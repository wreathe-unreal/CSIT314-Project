#pragma once

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
