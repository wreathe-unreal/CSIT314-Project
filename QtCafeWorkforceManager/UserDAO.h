#ifndef USERDAO_H
#define USERDAO_H
#include "Enums.h"
#include "User.h"
#include "Response.h"
#include <string>

#define DATABASE QApplicationGlobal::CafeDB

class UserDataAccessObject
{
    public:

        UserDataAccessObject(){};
        ~UserDataAccessObject(){};

        //uncoded
        ECommandResult Insert(User user);
        ECommandResult UpdateOrInsert(User user);
        ECommandResult Delete(std::string username);
        ECommandResult SetESR(std::string username, EStaffRole role);
        ECommandResult SetEUP(std::string username, EUserProfile profile);
        ECommandResult SetMaxSlots(std::string username, int maxSlots);
        User GetUser(const std::string& username);
        EUserProfile GetUserEUP(std::string username);
        EStaffRole GetUserESP(std::string username);
        int GetUserMaxSlots(std::string username);
        std::vector<User> GetByEUP(EUserProfile profile);
        std::vector<User> GetByESR(EStaffRole role);

        //coded
        Response Auth(QString username, QString password);
};

#endif // USERDAO_H
