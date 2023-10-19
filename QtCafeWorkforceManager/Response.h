#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include "Enums.h"
#include "User.h"
#include <QString>
#include <any>

class Response
{
    public:
        EDatabaseResult Result;
};

class AuthorizeResponse : public Response
{
    public:
        EUserProfile Profile;
        AuthorizeResponse (EDatabaseResult result, EUserProfile profile)
        {
            this->Result = result;
            this->Profile = profile;
        }
};
