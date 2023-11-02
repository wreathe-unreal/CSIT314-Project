#include "QApplicationGlobal.h"
#include "qcryptographichash.h"
#include <QString>
#include "PopUp.h"
#include "Response.h"

//define outside class for linker
Response<EUserProfile> AuthorizeController::DBResponse;
Response<QVector<User>>  GetUsersController::DBResponse;
Response<void> UpdateUserController::DBResponse;
Response<void> CreateUserController::DBResponse;
Response<void> DeleteUserController::DBResponse;
Response<QVector<User>> SearchUsersByEUPController::DBResponse;
Response<QVector<Slot>> CreateSlotController::DBResponse;
Response<QVector<Slot>> GetSlotsController::DBResponse;
Response<void> DeleteSlotController::DBResponse;
Response<QVector<Slot>> UpdateSlotController::DBResponse;
Response<QVector<Slot>> SearchSlotsByQDateController::DBResponse;
Response<QVector<Slot>> SearchSlotsByUserIDController::DBResponse;
Response<void> SetESRController::DBResponse;
Response<void> SetNameController::DBResponse;
Response<void> SetMaxSlotsController::DBResponse;
Response<User> GetUserController::DBResponse;
Response<void> CreateBidController::DBResponse;
Response<QVector<Bid>> GetPendingBidsController::DBResponse;
Response<Slot> GetSlotController::DBResponse;
Response<QVector<Bid>> SearchBidsByUserIDController::DBResponse;
Response<void> DeleteBidController::DBResponse;
Response<QVector<Bid>> SearchBidsBySlotIDController::DBResponse;
Response<QVector<User>> GetStaffController::DBResponse;
Response<User> GetUserByBidIDController::DBResponse;
Response<void> ApproveBidController::DBResponse;
Response<QVector<Bid>> GetBidsController::DBResponse;
Response<Bid> GetBidController::DBResponse;
Response<QVector<User>> GetBiddersBySlotIDController::DBResponse;
Response<void> UnapproveBidController::DBResponse;
Response<void> RejectBidController::DBResponse;
Response<QVector<Bid>> GetRejectedBidsByUserIDController::DBResponse;
Response<QVector<User>>  GetIdleStaffController::DBResponse;

Response<EUserProfile> AuthorizeController::Execute()
{
    QByteArray passwordBytes = Password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());

    return QApplicationGlobal::UserDAO.Authorize(Username, hashedPasswordHex);
}



Response<QVector<User>> GetUsersController::Execute()
{
    return QApplicationGlobal::UserDAO.GetUsers();
}

Response<void> UpdateUserController::Execute()
{
     //if the password did not change, simply update the user info
    Response<EUserProfile> authResponse = QApplicationGlobal::UserDAO.Authorize(this->UsernameBeforeUpdate, UpdatedUser.getPassword());
    if(authResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        return QApplicationGlobal::UserDAO.UpdateOrInsert(this->UpdatedUser, this->UsernameBeforeUpdate);
    }

    //if the password has changed, rehash the new plaint text password, and update
    QByteArray passwordBytes = UpdatedUser.getPassword().toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());
    UpdatedUser.setPassword(hashedPasswordHex);

    return QApplicationGlobal::UserDAO.UpdateOrInsert(this->UpdatedUser, this->UsernameBeforeUpdate);
}

Response<void> CreateUserController::Execute()
{
    QByteArray passwordBytes = NewUser.getPassword().toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());
    NewUser.setPassword(hashedPasswordHex);

    return QApplicationGlobal::UserDAO.Insert(this->NewUser);
}

Response<void> DeleteUserController::Execute()
{
    //first delete all of a user's bids...not the most efficient code..but for now...it works..
    Response<QVector<Bid>> allBidsResponse = QApplicationGlobal::BidDAO.GetBids();

    for(auto& b : allBidsResponse.Data)
    {
        if(b.UserID == this->UserID)
        {
            QApplicationGlobal::BidDAO.Delete(b.BidID);
        }
    }

    return QApplicationGlobal::UserDAO.Delete(this->UserID);
}

Response<QVector<User>> SearchUsersByEUPController::Execute()
{
    return QApplicationGlobal::UserDAO.SearchByEUP(this->profile);
}

Response<QVector<Slot>> CreateSlotController::Execute()
{
    return QApplicationGlobal::SlotDAO.CreateSlot(this->NewSlot);
}

Response<QVector<Slot>> GetSlotsController::Execute()
{
    return QApplicationGlobal::SlotDAO.GetAllSlots();

}

Response<void> DeleteSlotController::Execute()
{
    //first delete all bids associated with this slot
    QVector<Bid> bids = GetBidsController::Invoke().Data;

    for(auto&b : bids)
    {
        if(b.SlotID == this->SlotID)
        {
            DeleteBidController::Invoke(b.BidID);
        }
    }
    return QApplicationGlobal::SlotDAO.DeleteSlot(this->SlotID);
}

Response<QVector<Slot>> UpdateSlotController::Execute()
{
    return QApplicationGlobal::SlotDAO.UpdateSlot(this->SlotToEdit);
}

Response<QVector<Slot>> SearchSlotsByQDateController::Execute()
{
    return QApplicationGlobal::SlotDAO.SearchDate(this->Date);
}

Response<QVector<Slot>> SearchSlotsByUserIDController::Execute()
{
    return QApplicationGlobal::SlotDAO.SearchByUserID(this->UserID);
}

Response<void> SetESRController::Execute()
{
    return QApplicationGlobal::UserDAO.SetESR(this->Username, this->NewESR);
}

Response<void> SetNameController::Execute()
{
    return QApplicationGlobal::UserDAO.SetName(this->Username, this->NewName);
}

Response<void> SetMaxSlotsController::Execute()
{
    return QApplicationGlobal::UserDAO.SetMaxSlots(this->Username, this->MaxSlots);
}

Response<User> GetUserController::Execute()
{
    if(this->UserID == -1)
    {
        return QApplicationGlobal::UserDAO.GetUser(this->Username);

    }
    return QApplicationGlobal::UserDAO.GetUser(this->UserID);
}

Response<void> CreateBidController::Execute()
{
    return QApplicationGlobal::BidDAO.Insert(this->NewBid);
}

Response<QVector<Bid>> GetPendingBidsController::Execute()
{
    return QApplicationGlobal::BidDAO.GetPending();
}

Response<Slot> GetSlotController::Execute()
{
    return QApplicationGlobal::SlotDAO.GetSlot(this->SlotID);
}

Response<QVector<Bid>> SearchBidsByUserIDController::Execute()
{
    return QApplicationGlobal::BidDAO.SearchByUserID(this->UserID);
}

Response<void> DeleteBidController::Execute()
{
    return QApplicationGlobal::BidDAO.Delete(this->BidID);
}

Response<QVector<Bid>> SearchBidsBySlotIDController::Execute()
{
    return QApplicationGlobal::BidDAO.SearchBySlotID(this->SlotID);
}

Response<QVector<User>> GetStaffController::Execute()
{
    Response<QVector<int>> userIDResponse = QApplicationGlobal::BidDAO.GetStaff(this->SlotID);
    Response<QVector<User>> staffResponse;

    for(auto& id : userIDResponse.Data)
    {
        staffResponse.Data.push_back(QApplicationGlobal::UserDAO.GetUser(id).Data);
    }
    staffResponse.Result = EDatabaseResult::EDR_SUCCESS;
    return staffResponse;
}

Response<User> GetUserByBidIDController::Execute()
{
    return QApplicationGlobal::BidDAO.GetUserByBidID(this->BidID);
}

Response<void> ApproveBidController::Execute()
{
    return QApplicationGlobal::BidDAO.ApproveBid(this->BidID);
}

Response<Bid> GetBidController::Execute()
{
    return QApplicationGlobal::BidDAO.GetBid(this->BidID);
}


Response<QVector<User> > GetBiddersBySlotIDController::Execute()
{
    Response<QVector<int>> biddersIDResponse = QApplicationGlobal::BidDAO.GetBiddersBySlotID(this->SlotID);
    Response<QVector<User>> BiddersResponse;
    for(auto& uid : biddersIDResponse.Data)
    {
        BiddersResponse.Data.push_back(QApplicationGlobal::UserDAO.GetUser(uid).Data);
    }
    BiddersResponse.Result = EDatabaseResult::EDR_SUCCESS;
    return BiddersResponse;
}

Response<void> UnapproveBidController::Execute()
{
    return QApplicationGlobal::BidDAO.UnapproveBid(this->BidID);
}

Response<void> RejectBidController::Execute()
{
    return QApplicationGlobal::BidDAO.RejectBid(this->BidID);
}

Response<QVector<Bid> > GetRejectedBidsByUserIDController::Execute()
{
    return QApplicationGlobal::BidDAO.GetRejected(this->UserID);
}

Response<QVector<User> > GetIdleStaffController::Execute()
{
    Response<QVector<User>> userResponse = QApplicationGlobal::UserDAO.GetUsers();
    if(userResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error;
        error.AdminNoUserError();
        return userResponse;
    }

    Response<QVector<int>> bidderIDs = QApplicationGlobal::BidDAO.GetBiddersBySlotID(this->SlotID);
    Response<QVector<User>> bidderResponse;

    for(auto i : bidderIDs.Data)
    {
        bidderResponse.Data.push_back(QApplicationGlobal::UserDAO.GetUser(i).Data);
    }
    bidderResponse.Result = EDatabaseResult::EDR_SUCCESS;

    Response<QVector<User>> idleResponse;

    for (const User& user : userResponse.Data)
    {
        bool bFound = false;
        for (const User& bidder : bidderResponse.Data)
        {
            if (bidder.UserID == user.UserID)
            {
                bFound = true;
                break;
            }
        }
        if(!bFound && user.EUP == 3)
        {
            idleResponse.Data.push_back(user);
        }
    }

    idleResponse.Result = EDatabaseResult::EDR_SUCCESS;
    return idleResponse;

}

Response<QVector<Bid>> GetBidsController::Execute()
{
    return QApplicationGlobal::BidDAO.GetBids();
}
