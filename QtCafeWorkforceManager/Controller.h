#pragma once
#include "Bid.h"
#include "Enums.h"
#include "Slot.h"
#include "User.h"
#include <QString>
#include <QVector>
#include "Response.h"

//Empty Controller Interface
class IController
{
    public:
    IController(){};
   ~IController(){};
};

class SearchUsersByUsernameController : public IController
{
    public:

    static Response<QVector<User>> Invoke(QString username)
    {
       SearchUsersByUsernameController controller = SearchUsersByUsernameController(username);
       DBResponse = controller.Execute();
       return DBResponse;
    }
    static Response<QVector<User>> GetResponse()
    {
       return DBResponse;
    }

    private:
    static Response<QVector<User>> DBResponse;
    QString Username;
    SearchUsersByUsernameController(QString username)
    {
       this->Username = username;
    }
    Response<QVector<User>> Execute();
};

class AuthorizeController : public IController
{
   public:

        static Response<EUserProfile> Invoke(QString username, QString password)
        {
            AuthorizeController controller = AuthorizeController(username, password);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<EUserProfile> GetResponse()
        {
            return DBResponse;
        }

    private:
        static Response<EUserProfile> DBResponse;
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
        static Response<QVector<User>> Invoke()
        {
           GetUsersController controller = GetUsersController();
           DBResponse = controller.Execute();
           return DBResponse;
        }
        static Response<QVector<User>> GetResponse()
        {
           return DBResponse;
        }

    private:
        static Response<QVector<User>>  DBResponse;
        Response<QVector<User>> Execute();
};

class UpdateUserController : public IController
{
   public:
       static Response<void> Invoke(User updatedUser, QString usernameBeforeUpdate)
        {
           UpdateUserController controller = UpdateUserController(updatedUser, usernameBeforeUpdate);
           DBResponse = controller.Execute();
           return DBResponse;
        }

        static Response<void> GetResponse()
        {
           return DBResponse;
        }

   private:
        static Response<void> DBResponse;
        UpdateUserController(User updatedUser, QString usernameBeforeUpdate)
        {
           this->UpdatedUser = updatedUser;
           this->UsernameBeforeUpdate = usernameBeforeUpdate;
        }
       QString UsernameBeforeUpdate;
       User UpdatedUser;
       Response<void> Execute();
};

class CreateUserController : public IController
{
   public:
       static Response<void> Invoke(User newUser)
       {
           CreateUserController controller = CreateUserController(newUser);
           DBResponse = controller.Execute();
           return DBResponse;
       }
       static Response<void> GetResponse()
       {
           return DBResponse;
       }

   private:
       User NewUser;
       static Response<void> DBResponse;

       CreateUserController(User newUser)
       {
            this->NewUser = newUser;
       }


       Response<void> Execute();
};

class DeleteUserController : public IController
{
   public:
       static Response<void> Invoke(int userid)
       {
            DeleteUserController controller = DeleteUserController(userid);
            DBResponse = controller.Execute();
            return DBResponse;
       }
       static Response<void> GetResponse()
       {
            return DBResponse;
       }

   private:
       static Response<void> DBResponse;
       int UserID;

       DeleteUserController(int userID)
       {
            this->UserID = userID;
       }

       Response<void> Execute();
};

class SearchUsersByEUPController : public IController
{
   public:
       static Response<QVector<User>> Invoke(EUserProfile userProfile)
       {
            SearchUsersByEUPController controller = SearchUsersByEUPController(userProfile);
            DBResponse = controller.Execute();
            return DBResponse;

       }
       static Response<QVector<User>> GetResponse()
       {
            return DBResponse;
       }
   private:
       EUserProfile profile;
       static Response<QVector<User>> DBResponse;
       SearchUsersByEUPController(EUserProfile userProfile)
       {
            this->profile = userProfile;
       }

       Response<QVector<User>> Execute();
};


class CreateSlotController: public IController
{
   public:
       static Response<QVector<Slot>> Invoke(Slot newSlot)
       {
            CreateSlotController controller = CreateSlotController(newSlot);
            DBResponse = controller.Execute();
            return DBResponse;
       }
       static Response<QVector<Slot>> GetResponse()
       {
            return DBResponse;
       }

   private:
       Slot NewSlot;
       static Response<QVector<Slot>> DBResponse;
       CreateSlotController(Slot newslot)
       {
            this->NewSlot = newslot;
       }

       Response<QVector<Slot>> Execute();
};

class GetSlotsController: public IController
{
   public:
       static Response<QVector<Slot>> Invoke()
       {
            GetSlotsController controller = GetSlotsController();
            DBResponse = controller.Execute();
            return DBResponse;
       }
       static Response<QVector<Slot>> GetResponse()
       {
            return DBResponse;
       }

   private:
       static Response<QVector<Slot>> DBResponse;
       GetSlotsController(){}
       Response<QVector<Slot>> Execute();
};

class DeleteSlotController: public IController
{
   public:
       static Response<void> Invoke(int slotID)
       {
            DeleteSlotController controller = DeleteSlotController(slotID);
            DBResponse = controller.Execute();
            return DBResponse;
       }
       static Response<void> GetResponse()
       {
            return DBResponse;
       }
   private:
       static Response<void> DBResponse;
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
        static Response<QVector<Slot>> Invoke(Slot updatedSlot)
        {
            UpdateSlotController controller = UpdateSlotController(updatedSlot);
            DBResponse = controller.Execute();
            return DBResponse;
        }

        static Response<QVector<Slot>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<Slot>> DBResponse;
        Slot SlotToEdit;
        UpdateSlotController(Slot slotToEdit)
        {
            this->SlotToEdit = slotToEdit;
        }

        Response<QVector<Slot>> Execute();
};

class SearchSlotsByQDateController : public IController
{
    public:
        static Response<QVector<Slot>> Invoke(QDate date)
        {
            SearchSlotsByQDateController controller = SearchSlotsByQDateController(date);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<Slot>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<Slot>> DBResponse;
        QDate Date;
        SearchSlotsByQDateController(QDate date)
        {
            this->Date = date;
        }
        Response<QVector<Slot>> Execute();
};


class SearchSlotsByUserIDController : public IController
{
    public:
        static Response<QVector<Slot>> Invoke(int userID)
        {
            SearchSlotsByUserIDController controller = SearchSlotsByUserIDController(userID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<Slot>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<Slot>> DBResponse;
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
        static Response<void> Invoke(QString username, EStaffRole newESR)
        {
            SetESRController controller = SetESRController(username, newESR);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<void> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<void> DBResponse;
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
        static Response<void> Invoke(QString username, QString newName)
        {
            SetNameController controller = SetNameController(username, newName);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<void> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<void> DBResponse;
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
        static Response<void> Invoke(QString username, int maxSlots)
        {
            SetMaxSlotsController controller = SetMaxSlotsController(username, maxSlots);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<void> GetResponse()
        {
            return DBResponse;
        }
    public:
        static Response<void> DBResponse;
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
        static Response<User> Invoke(QString username)
        {
            GetUserController controller = GetUserController(username);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<User> Invoke(int userID)
        {
            GetUserController controller = GetUserController(userID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<User> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<User> DBResponse;
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

class CreateBidController : public IController
{
    public:
        static Response<Bid> Invoke(Bid newBid)
        {
            CreateBidController controller = CreateBidController(newBid);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<Bid> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<Bid> DBResponse;
        Bid NewBid;
        CreateBidController(Bid newBid)
        {
            this->NewBid = newBid;
        }
        Response<Bid> Execute();
};

class GetPendingBidsController : public IController
{
    public:
        static Response<QVector<Bid>> Invoke()
        {
            GetPendingBidsController controller = GetPendingBidsController();
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<Bid>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<Bid>> DBResponse;
        GetPendingBidsController()
        {

        }
        Response<QVector<Bid>> Execute();
};

class GetSlotController : public IController
{
    public:
        static Response<Slot> Invoke(int slotID)
        {
            GetSlotController controller = GetSlotController(slotID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<Slot> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<Slot> DBResponse;
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
        static Response<QVector<Bid>> Invoke(int userID)
        {
            SearchBidsByUserIDController controller = SearchBidsByUserIDController(userID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<Bid>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<Bid>> DBResponse;
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
        static Response<void> Invoke(int bidID)
        {
            DeleteBidController controller = DeleteBidController(bidID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<void> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<void> DBResponse;
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
        static Response<QVector<Bid>> Invoke(int slotID)
        {
            SearchBidsBySlotIDController controller = SearchBidsBySlotIDController(slotID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<Bid>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<Bid>> DBResponse;
        int SlotID;
        SearchBidsBySlotIDController(int slotID)
        {
            this->SlotID = slotID;
        }
        Response<QVector<Bid>> Execute();
};

class GetStaffController : public IController
{
    public:
        static Response<QVector<User>> Invoke(int slotID)
        {
            GetStaffController controller = GetStaffController(slotID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<User>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<User>> DBResponse;
        int SlotID;
        GetStaffController(int slotid)
        {
            this->SlotID = slotid;
        }
        Response<QVector<User>> Execute();
};

class GetUserByBidIDController : public IController
{
    public:
        static Response<User> Invoke(int bidID)
        {
            GetUserByBidIDController controller = GetUserByBidIDController(bidID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<User> GetResponse()
        {
            return DBResponse;
        }

    private:
        static Response<User> DBResponse;
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
        static Response<void> Invoke(int bidid)
        {
            ApproveBidController controller = ApproveBidController(bidid);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<void> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<void> DBResponse;
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
        static Response<Bid> Invoke(int bidid)
        {
            GetBidController controller = GetBidController(bidid);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<Bid> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<Bid> DBResponse;
        int BidID;
        GetBidController(int bidid)
        {
            this->BidID = bidid;
        }
        Response<Bid> Execute();
};

class GetBidsController : public IController
{
    public:
        static Response<QVector<Bid>> Invoke()
        {
            GetBidsController controller = GetBidsController();
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<Bid>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<Bid>> DBResponse;
        GetBidsController()
        {
        }
        Response<QVector<Bid>> Execute();
};

class GetBiddersBySlotIDController : public IController
{
    public:
        static Response<QVector<User>> Invoke(int slotID)
        {
            GetBiddersBySlotIDController controller = GetBiddersBySlotIDController(slotID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<User>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<User>> DBResponse;
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
        static Response<void> Invoke(int bidid)
        {
            UnapproveBidController controller = UnapproveBidController(bidid);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<void> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<void> DBResponse;
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
        static Response<void> Invoke(int bidid)
        {
            RejectBidController controller = RejectBidController(bidid);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<void> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<void> DBResponse;
        int BidID;
        RejectBidController(int bidID)
        {
            this->BidID = bidID;
        }
        Response<void> Execute();
};

class GetRejectedBidsByUserIDController : public IController
{
    public:
        static Response<QVector<Bid>> Invoke(int userID)
        {
            GetRejectedBidsByUserIDController controller = GetRejectedBidsByUserIDController(userID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<Bid>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<Bid>> DBResponse;
        int UserID;
        GetRejectedBidsByUserIDController(int userID)
        {
            this->UserID = userID;
        }

        Response<QVector<Bid>> Execute();
};

class GetIdleStaffController : public IController
{
    public:
        static Response<QVector<User>> Invoke(int slotID)
        {
            GetIdleStaffController controller = GetIdleStaffController(slotID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<QVector<User>> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<QVector<User>>  DBResponse;
        int SlotID;
        GetIdleStaffController(int slotID)
        {
            this->SlotID = slotID;
        }
        Response<QVector<User>> Execute();
};

class UpdateBidController : public IController
{
    public:
        static Response<void> Invoke(Bid newBid, int slotID)
        {
            UpdateBidController controller = UpdateBidController(newBid, slotID);
            DBResponse = controller.Execute();
            return DBResponse;
        }
        static Response<void> GetResponse()
        {
            return DBResponse;
        }
    private:
        static Response<void> DBResponse;
        Bid NewBid;
        int SlotID;
        UpdateBidController(Bid newBid, int slotID)
        {
            this->NewBid = newBid;
            this->SlotID = slotID;
        }

        Response<void> Execute();
};
