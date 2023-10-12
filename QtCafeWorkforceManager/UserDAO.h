#ifndef USERDAO_H
#define USERDAO_H
#include "Enums.h"
#include "User.h"

class UserDAO
{
    public:
        UserDAO(){};
        ~UserDAO(){};

        ECommandResult InsertUser(const User& user);

};

#endif // USERDAO_H
