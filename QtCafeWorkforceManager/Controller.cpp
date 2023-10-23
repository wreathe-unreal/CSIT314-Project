#include "QApplicationGlobal.h"
#include "qcryptographichash.h"
#include <QString>

EUserProfile AuthorizeController::Execute()
{
    QByteArray passwordBytes = Password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());

    return QApplicationGlobal::UserDAO.Authorize(Username, hashedPasswordHex);
}



QVector<User> GetUsersController::Execute()
{
    return QApplicationGlobal::UserDAO.GetUsers();
}

void UpdateUserController::Execute()
{
     //if the password did not change, simply update the user info
    QApplicationGlobal::UserDAO.Authorize(this->UsernameBeforeUpdate, UpdatedUser.getPassword());
    if(QApplicationGlobal::UserDAO.Result == EDatabaseResult::EDR_SUCCESS)
    {
        qDebug() << "no pw change, updating, current password: " << UpdatedUser.getPassword();
        QApplicationGlobal::UserDAO.UpdateOrInsert(this->UpdatedUser, this->UsernameBeforeUpdate);
        return;
    }

    qDebug() << "pw change, updating, current password: " << UpdatedUser.getPassword();
    //if the password has changed, rehash the new plaint text password, and update
    QByteArray passwordBytes = UpdatedUser.getPassword().toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());
    UpdatedUser.setPassword(hashedPasswordHex);

    QApplicationGlobal::UserDAO.UpdateOrInsert(this->UpdatedUser, this->UsernameBeforeUpdate);
}

void CreateUserController::Execute()
{
    QByteArray passwordBytes = NewUser.getPassword().toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());
    NewUser.setPassword(hashedPasswordHex);

    QApplicationGlobal::UserDAO.Insert(this->NewUser);
}

void DeleteUserController::Execute()
{
    QApplicationGlobal::UserDAO.Delete(this->UsernameToDelete);
}

QVector<User> SearchByEUPController::Execute()
{
    return QApplicationGlobal::UserDAO.SearchByEUP(this->profile);
}

QVector<Slot> CreateSlotController::Execute()
{
    return QApplicationGlobal::SlotDAO.CreateSlot(this->NewSlot);
}

QVector<Slot> GetSlotsController::Execute()
{
    return QApplicationGlobal::SlotDAO.GetAllSlots();

}

void DeleteSlotController::Execute()
{
    return QApplicationGlobal::SlotDAO.DeleteSlot(this->SlotID);
}

QVector<Slot> UpdateSlotController::Execute()
{
    return QApplicationGlobal::SlotDAO.UpdateSlot(this->SlotToEdit);
}

QVector<Slot> SearchSlotByDayController::Execute()
{
    return QApplicationGlobal::SlotDAO.SearchDate(this->Date);
}

void IsUserActiveController::Execute()
{
    return QApplicationGlobal::UserDAO.IsUserActive(this->Username);
}
