#pragma once

#include "Enums.h"
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


