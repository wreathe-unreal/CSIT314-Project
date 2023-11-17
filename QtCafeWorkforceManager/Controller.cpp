#include "qcryptographichash.h"
#include <QString>
#include "QApplicationGlobal.h"
#include "PopUp.h"
#include "Response.h"
#include "Controller.h"
#include "User.h"
#include "Slot.h"
#include "Bid.h"

//Below we define static objects outside class for linker recognition
//we will also use this space to assign user stories to controllers

//As a System Admin, I want to be able to log out the system
//As a Cafe Staff, I want to be able to log out of the system
//As a Cafe Manager, I want to be able to log out the system
//As a Cafe Owner, I want to be able to log out the system
//No Controller needed, the boundary itself closes itself and opens a new AuthWindow

//As a Cafe Staff, I want to be able to log into the system
//As a Cafe Manager, I want to be able to log into the system
//As a Cafe Owner, I want to be able to log in the system
//As a System Admin, I want to be able to log in the system
Response<EUserProfile> AuthorizeController::DBResponse;

//As a System Admin, I want to be able to view a list of user accounts
Response<QVector<User>>  GetUsersController::DBResponse;

//As a System Admin, I want to be able to update user accounts
//As a System Admin, I want to be able to suspend user accounts
//As a System Admin, I want to be able to update user profiles
//As a System Admin, I want to be able to suspend user profiles
Response<void> UpdateUserController::DBResponse;

//As a System Admin, I want to be able to create user accounts
//As a System Admin I want to be able to create user profiles
Response<void> CreateUserController::DBResponse;

//As a System Admin, I want to be able to delete user accounts
Response<void> DeleteUserController::DBResponse;

//As a System Admin, I want to be able to search for user accounts
Response<QVector<User>> SearchUsersByEUPController::DBResponse;
Response<QVector<User>> SearchUsersByUsernameController::DBResponse;

//As a Cafe Owner, I want to be able to create work slots
Response<QVector<Slot>> CreateSlotController::DBResponse;

//As a Cafe Owner, I want to be able to view the work slots
//As a Cafe Staff I want to be able to view all work slots
//As a Cafe Manager, I want to be able to view all work slots
Response<QVector<Slot>> GetSlotsController::DBResponse;

//As a Cafe Owner, I want to be able to delete a work slot
Response<void> DeleteSlotController::DBResponse;

//As a Cafe Owner, I want to be able to update a work slot
Response<QVector<Slot>> UpdateSlotController::DBResponse;

//As a Cafe Manager, I want to be able to search for work slots without a minimum number of staff
//As a Cafe Owner, I want to be able to search for a particular work slot
Response<QVector<Slot>> SearchSlotsByQDateController::DBResponse;

//As a Cafe Staff, I want to be able to search through all work slots
Response<QVector<Slot>> SearchSlotsByUserIDController::DBResponse;

//As a Cafe Staff, I want to be able to select my role in the cafe
Response<void> SetESRController::DBResponse;

//Allows Cafe Staff to set their name
Response<void> SetNameController::DBResponse;

//As a Cafe Staff, I want to be able to choose my maximum number of work slots
Response<void> SetMaxSlotsController::DBResponse;

//As a System Admin, I want to be able to view user profiles
Response<User> GetUserController::DBResponse;

//As a Cafe Staff, I want to be able to create a bid for a work slot
Response<Bid> CreateBidController::DBResponse;

//Allows a more specific search for bids
Response<QVector<Bid>> GetPendingBidsController::DBResponse;

//Gets a specific slot
Response<Slot> GetSlotController::DBResponse;

//Gets the bids for a specific slot
Response<QVector<Bid>> SearchBidsBySlotIDController::DBResponse;

//Gets the staff approved for a specific slotID
Response<QVector<User>> GetStaffController::DBResponse;

//gets the user associated with a specific bid
Response<User> GetUserByBidIDController::DBResponse;

//As a Cafe Staff, I want to be able to change my current bids
Response<void> UpdateBidController::DBResponse;

//As a Cafe Staff, I want to be able to view all my current bids
//As a Cafe Staff, I want to be able to check my bid approvals NOTE!! WE filter for approved bids on boundary
Response<QVector<Bid>> SearchBidsByUserIDController::DBResponse;

//As a Cafe Staff, I want to be able to delete my bids
Response<void> DeleteBidController::DBResponse;

//As a Cafe Manager, I want to be able to update the bids’ approval status
//As a Cafe Manager, I want to be able to assign available staff to a work slot
Response<void> ApproveBidController::DBResponse;

//As a Cafe Manager, I want to be able to view the cafe staffs’ bids
Response<QVector<Bid>> GetBidsController::DBResponse;

//gets a specific bid
Response<Bid> GetBidController::DBResponse;

//gets bidders by slotID
Response<QVector<User>> GetBiddersBySlotIDController::DBResponse;

//As a Cafe Manager, I want to be able to update the bids’ approval status
Response<void> UnapproveBidController::DBResponse;

//As a Cafe Manager, I want to be able to update the bids’ approval status
Response<void> RejectBidController::DBResponse;

//gets a user's rejected bids
Response<QVector<Bid>> GetRejectedBidsByUserIDController::DBResponse;

//As a Cafe Manager, I want to be able to view the list of available cafe staff
Response<QVector<User>>  GetIdleStaffController::DBResponse;

//end user story breakdown


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
    QVector<Bid> bids = Bid::GetBids().Data;

    for(auto&b : bids)
    {
        if(b.SlotID == this->SlotID)
        {
            Bid::Delete(b.BidID);
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

Response<Bid> CreateBidController::Execute()
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

//get staff without bids for a slot id
Response<QVector<User> > GetIdleStaffController::Execute()
{
    //first get all users
    Response<QVector<User>> userResponse = User::GetUsers();
    if(userResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error;
        error.AdminNoUserError();
        return userResponse;
    }

    //get all bidders for a slot by slot id
    Response<QVector<int>> bidderIDs = Bid::GetBiddersBySlotID(this->SlotID);
    Response<QVector<User>> bidderResponse;

    for(auto i : bidderIDs.Data)
    {
        bidderResponse.Data.push_back(User::GetUser(i).Data);
    }
    bidderResponse.Result = EDatabaseResult::EDR_SUCCESS;

    Response<QVector<User>> idleResponse;

    //we loop through the list of bidding users and the list of all users and if the user does not have a bid
    //we add him to the list of users we will return of "idle staff"
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


//inserts a new bid and deletes the old bid
Response<void> UpdateBidController::Execute()
{
    Response<void> UpdateResponse;

    if(Bid::Insert(this->NewBid).Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp dialogBox;
        dialogBox.StaffBidConflictError();
        UpdateResponse.Result = EDatabaseResult::EDR_FAILURE;
        return UpdateResponse;
    }

    Response<QVector<Bid>> bidSlotResponse = Bid::SearchBySlotID(this->SlotID);


    Response<void> deleteResponse;
    for(auto& b : bidSlotResponse.Data)
    {
        if(b.UserID == QApplicationGlobal::CurrentUserID)
        {
            deleteResponse = Bid::Delete(b.BidID);

        }
    }

    if(deleteResponse.Result == EDatabaseResult::EDR_FAILURE)
    {
        PopUp error = PopUp();
        error.StaffDeleteDuringUpdateError();
        error.exec();
        UpdateResponse.Result = EDatabaseResult::EDR_FAILURE;
        return UpdateResponse;
    }
    UpdateResponse.Result = EDatabaseResult::EDR_SUCCESS;

    PopUp dialogBox;
    dialogBox.StaffBidSubmitted();
    return UpdateResponse;
}

Response<QVector<User> > SearchUsersByUsernameController::Execute()
{
    return User::SearchByUsername(this->Username);
}
