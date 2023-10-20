#pragma once

#include "Enums.h"
#include "User.h"
#include <QString>

class IController
{
    public:
    IController(){};
   ~IController(){};
};

class AuthorizeController : public IController
{
   public:
    QString Username;
    QString Password;

   AuthorizeController(QString username, QString password)
   {
       Username = username;
       Password = password;
   }

   EUserProfile Execute();

};


class GetUsersController : public IController
{
    public:
        QVector<User> Execute();
};

class UpdateUserController : public IController
{
    public:
        QString UsernameBeforeUpdate;
       User UpdatedUser;

       UpdateUserController(User updatedUser, QString usernameBeforeUpdate)
       {
            this->UpdatedUser = updatedUser;
            this->UsernameBeforeUpdate = usernameBeforeUpdate;
       }


       void Execute();
};

class CreateUserController : public IController
{
   public:
       User NewUser;

       CreateUserController(User newUser)
       {
            this->NewUser = newUser;
       }


       void Execute();
};

class DeleteUserController : public IController
{
   public:
       QString UsernameToDelete;

       DeleteUserController(QString usernameToDelete)
       {
            this->UsernameToDelete = usernameToDelete;
       }

       void Execute();
};

class SearchByEUPController : public IController
{
   public:
       EUserProfile profile;

       SearchByEUPController(EUserProfile userProfile)
       {
            this->profile = userProfile;
       }

       QVector<User> Execute();
};

