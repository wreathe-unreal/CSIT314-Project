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

Response<void> IsUserActiveController::Execute()
{
    return QApplicationGlobal::UserDAO.IsUserActive(this->Username);
}

Response<QVector<Slot>> SearchSlotsByUserIDController::Execute()
{
    return QApplicationGlobal::SlotDAO.SearchByUserID(this->UserID);
}

Response<int> GetUserIDController::Execute()
{
    return QApplicationGlobal::UserDAO.GetUserID(this->Username);
}

Response<EUserProfile> GetEUPController::Execute()
{
    return QApplicationGlobal::UserDAO.GetEUP(this->Username);
}

Response<EStaffRole> GetESRController::Execute()
{
    return QApplicationGlobal::UserDAO.GetESR(this->Username);
}

Response<void> SetESRController::Execute()
{
    return QApplicationGlobal::UserDAO.SetESR(this->Username, this->NewESR);
}

Response<QString> GetNameController::Execute()
{
    return QApplicationGlobal::UserDAO.GetName(this->Username);
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
    return QApplicationGlobal::UserDAO.GetUser(this->Username);
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
