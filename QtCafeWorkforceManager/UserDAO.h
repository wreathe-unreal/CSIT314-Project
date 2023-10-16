#ifndef USERDAO_H
#define USERDAO_H
#include "Enums.h"
#include "QApplicationGlobal.h"
#include "User.h"
#include "Response.h"
#include "NewUser.h"
#include <string>

class UserDataAccessObject
{
    public:

        UserDataAccessObject(){};
        ~UserDataAccessObject(){};

        //coded
        ECommandResult Insert(NewUser newUser);
        QVector<User> GetByESR(EStaffRole role);
        QVector<User> GetByEUP(EUserProfile profile);
        Response Auth(QString username, QString password); //response json = EUP
        int GetMaxSlots(std::string username);
        EUserProfile GetEUP(std::string username);
        EStaffRole GetESR(std::string username);
        User GetUser(const std::string& username);
        ECommandResult UpdateOrInsert(User user);
        ECommandResult SetMaxSlots(std::string username, int maxSlots);
        ECommandResult SetEUP(std::string username, EUserProfile profile);
        ECommandResult SetESR(std::string username, EStaffRole role);
        ECommandResult Delete(std::string username);
        QVector<Slot> GetSlotsByUser(std::string username);
        Response GetbActive(std::string username);
        ECommandResult SuspendUser(std::string username);


};

#endif // USERDAO_H
