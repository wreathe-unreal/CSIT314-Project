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

    UserDataAccessObject(){};
    ~UserDataAccessObject(){};

    //coded
    void Insert(User user);
    QVector<User> SearchByESR(EStaffRole role);
    QVector<User> SearchByEUP(EUserProfile profile);
    EUserProfile Authorize(QString username, QString password);
    int GetMaxSlots(std::string username);
    EUserProfile GetEUP(std::string username);
    EStaffRole GetESR(std::string username);
    User GetUser(const std::string& username);
    void UpdateOrInsert(User user, QString usernameBeforeUpdate);
    void SetMaxSlots(std::string username, int maxSlots);
    void SetEUP(std::string username, EUserProfile profile);
    void SetESR(std::string username, EStaffRole role);
    void Delete(QString username);
    QVector<User> GetUsers();

    QVector<Slot> GetSlotsByUser(std::string username);
    bool GetbActive(std::string username);
    void SuspendUser(std::string username);


};

#endif // USERDAO_H
