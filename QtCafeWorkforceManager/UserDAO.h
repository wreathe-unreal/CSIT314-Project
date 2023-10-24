#ifndef USERDAO_H
#define USERDAO_H
#include "Enums.h"
#include "QApplicationGlobal.h"
#include "User.h"
#include <string>

class UserDataAccessObject
{
    public:
    EDatabaseResult Result;

    UserDataAccessObject()
    {
        Result = EDatabaseResult::EDR_UNINITIALIZED;

    };
    ~UserDataAccessObject(){};

    //coded
    void IsUserActive(QString username);
    void Insert(User user);
    QVector<User> SearchByESR(EStaffRole role);
    QVector<User> SearchByEUP(EUserProfile profile);
    EUserProfile Authorize(QString username, QString password);
    int GetMaxSlots(std::string username);
    EUserProfile GetEUP(QString username);
    EStaffRole GetESR(QString username);
    User GetUser(const std::string& username);
    void UpdateOrInsert(User user, QString usernameBeforeUpdate);
    void SetMaxSlots(std::string username, int maxSlots);
    void SetEUP(QString username, EUserProfile profile);
    void SetESR(QString username, EStaffRole role);
    void Delete(QString username);
    QVector<User> GetUsers();

    QVector<Slot> GetSlotsByUser(QString username);
    bool GetbActive(std::string username);
    void SuspendUser(std::string username);
    int GetUserID(QString username);


};

#endif // USERDAO_H
