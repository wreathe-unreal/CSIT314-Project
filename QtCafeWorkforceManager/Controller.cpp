#include "qcryptographichash.h"
#include <QString>
#include "PopUp.h"
#include "Response.h"
#include "Controller.h"
#include "User.h"
#include "Slot.h"
#include "Bid.h"

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

    return User::Authorize(Username, hashedPasswordHex);
}



Response<QVector<User>> GetUsersController::Execute()
{
    return User::GetUsers();
}

Response<void> UpdateUserController::Execute()
{
     //if the password did not change, simply update the user info
    Response<EUserProfile> authResponse = User::Authorize(this->UsernameBeforeUpdate, UpdatedUser.getPassword());
    if(authResponse.Result == EDatabaseResult::EDR_SUCCESS)
    {
        return User::UpdateOrInsert(this->UpdatedUser, this->UsernameBeforeUpdate);
    }

    //if the password has changed, rehash the new plaint text password, and update
    QByteArray passwordBytes = UpdatedUser.getPassword().toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());
    UpdatedUser.setPassword(hashedPasswordHex);

    return User::UpdateOrInsert(this->UpdatedUser, this->UsernameBeforeUpdate);
}

Response<void> CreateUserController::Execute()
{
    QByteArray passwordBytes = NewUser.getPassword().toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());
    NewUser.setPassword(hashedPasswordHex);

    return User::Insert(this->NewUser);
}

Response<void> DeleteUserController::Execute()
{
    //first delete all of a user's bids...not the most efficient code..but for now...it works..
    Response<QVector<Bid>> allBidsResponse = Bid::GetBids();

    for(auto& b : allBidsResponse.Data)
    {
        if(b.UserID == this->UserID)
        {
            Bid::Delete(b.BidID);
        }
    }

    return User::Delete(this->UserID);
}

Response<QVector<User>> SearchUsersByEUPController::Execute()
{
    return User::SearchByEUP(this->profile);
}

Response<QVector<Slot>> CreateSlotController::Execute()
{
    return Slot::CreateSlot(this->NewSlot);
}

Response<QVector<Slot>> GetSlotsController::Execute()
{
    return Slot::GetAllSlots();

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
    return Slot::DeleteSlot(this->SlotID);
}

Response<QVector<Slot>> UpdateSlotController::Execute()
{
    return Slot::UpdateSlot(this->SlotToEdit);
}

Response<QVector<Slot>> SearchSlotsByQDateController::Execute()
{
    return Slot::SearchDate(this->Date);
}

Response<QVector<Slot>> SearchSlotsByUserIDController::Execute()
{
    return Slot::SearchByUserID(this->UserID);
}

Response<void> SetESRController::Execute()
{
    return User::SetESR(this->Username, this->NewESR);
}

Response<void> SetNameController::Execute()
{
    return User::SetName(this->Username, this->NewName);
}

Response<void> SetMaxSlotsController::Execute()
{
    return User::SetMaxSlots(this->Username, this->MaxSlots);
}

Response<User> GetUserController::Execute()
{
    if(this->UserID == -1)
    {
        return User::GetUser(this->Username);

    }
    return User::GetUser(this->UserID);
}

Response<void> CreateBidController::Execute()
{
    return Bid::Insert(this->NewBid);
}

Response<QVector<Bid>> GetPendingBidsController::Execute()
{
    return Bid::GetPending();
}

Response<Slot> GetSlotController::Execute()
{
    return Slot::GetSlot(this->SlotID);
}

Response<QVector<Bid>> SearchBidsByUserIDController::Execute()
{
    return Bid::SearchByUserID(this->UserID);
}

Response<void> DeleteBidController::Execute()
{
    return Bid::Delete(this->BidID);
}

Response<QVector<Bid>> SearchBidsBySlotIDController::Execute()
{
    return Bid::SearchBySlotID(this->SlotID);
}

Response<QVector<User>> GetStaffController::Execute()
{
    Response<QVector<int>> userIDResponse = Bid::GetStaff(this->SlotID);
    Response<QVector<User>> staffResponse;

    for(auto& id : userIDResponse.Data)
    {
        staffResponse.Data.push_back(User::GetUser(id).Data);
    }
    staffResponse.Result = EDatabaseResult::EDR_SUCCESS;
    return staffResponse;
}

Response<User> GetUserByBidIDController::Execute()
{
    return Bid::GetUserByBidID(this->BidID);
}

Response<void> ApproveBidController::Execute()
{
    return Bid::ApproveBid(this->BidID);
}

Response<Bid> GetBidController::Execute()
{
    return Bid::GetBid(this->BidID);
}


Response<QVector<User> > GetBiddersBySlotIDController::Execute()
{
    Response<QVector<int>> biddersIDResponse = Bid::GetBiddersBySlotID(this->SlotID);
    Response<QVector<User>> BiddersResponse;
    for(auto& uid : biddersIDResponse.Data)
    {
        BiddersResponse.Data.push_back(User::GetUser(uid).Data);
    }
    BiddersResponse.Result = EDatabaseResult::EDR_SUCCESS;
    return BiddersResponse;
}

Response<void> UnapproveBidController::Execute()
{
    return Bid::UnapproveBid(this->BidID);
}

Response<void> RejectBidController::Execute()
{
    return Bid::RejectBid(this->BidID);
}

Response<QVector<Bid> > GetRejectedBidsByUserIDController::Execute()
{
    return Bid::GetRejected(this->UserID);
}

Response<QVector<User> > GetIdleStaffController::Execute()
{
    Response<QVector<User>> userResponse = User::GetUsers();
    if(userResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error;
        error.AdminNoUserError();
        return userResponse;
    }

    Response<QVector<int>> bidderIDs = Bid::GetBiddersBySlotID(this->SlotID);
    Response<QVector<User>> bidderResponse;

    for(auto i : bidderIDs.Data)
    {
        bidderResponse.Data.push_back(User::GetUser(i).Data);
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
    return Bid::GetBids();
}
