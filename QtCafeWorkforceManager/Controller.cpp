#include "QApplicationGlobal.h"
#include "qcryptographichash.h"
#include <QString>
#include "Response.h"

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
    return QApplicationGlobal::UserDAO.Delete(this->UsernameToDelete);
}

Response<QVector<User>> SearchByEUPController::Execute()
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
    return QApplicationGlobal::SlotDAO.DeleteSlot(this->SlotID);
}

Response<QVector<Slot>> UpdateSlotController::Execute()
{
    return QApplicationGlobal::SlotDAO.UpdateSlot(this->SlotToEdit);
}

Response<QVector<Slot>> SearchSlotByDayController::Execute()
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

Response<void> InsertBidController::Execute()
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

Response<QVector<User>> SearchWorkersBySlotIDController::Execute()
{
    return QApplicationGlobal::BidDAO.GetStaff(this->SlotID);
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

Response<QVector<User> > GetApprovedUsersBySlotController::Execute()
{
    return QApplicationGlobal::BidDAO.GetStaff(this->SlotID);
}

Response<QVector<User> > GetBiddersBySlotIDController::Execute()
{
    return QApplicationGlobal::BidDAO.GetBidders(this->SlotID);
}
