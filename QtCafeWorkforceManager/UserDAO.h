#ifndef USERDAO_H
#define USERDAO_H
#include "Enums.h"
#include "QApplicationGlobal.h"
#include "Response.h"
#include "User.h"

class UserDataAccessObject
{
    public:
    UserDataAccessObject(){};
    ~UserDataAccessObject(){};

    //coded
    Response<void> IsUserActive(QString username);
    Response<void> Insert(User user);
    Response<QVector<User>> SearchByESR(EStaffRole role);
    Response<QVector<User>> SearchByEUP(EUserProfile profile);
    Response<EUserProfile> Authorize(QString username, QString password);
    Response<int> GetMaxSlots(std::string username);
    Response<EUserProfile> GetEUP(QString username);
    Response<EStaffRole> GetESR(QString username);
    Response<User> GetUser(QString username);
    Response<void> UpdateOrInsert(User user, QString usernameBeforeUpdate);
    Response<void> SetMaxSlots(QString username, int maxSlots);
    Response<void> SetEUP(QString username, EUserProfile profile);
    Response<void> SetESR(QString username, EStaffRole role);
    Response<void> Delete(QString username);
    Response<QVector<User>> GetUsers();
    Response<QString> GetName(QString username);
    Response<void> SetName(QString username, QString newName);
    Response<QVector<Slot>> GetSlotsByUser(QString username);
    Response<bool> GetbActive(QString username);
    Response<void> SuspendUser(QString username);
    Response<int> GetUserID(QString username);


};

#endif // USERDAO_H
