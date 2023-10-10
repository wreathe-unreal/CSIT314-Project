#include <string>

#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

using namespace std;

enum ECommandType
{
    ECT_Update,
    ECT_Authorize,
    ECT_Create,
};


class ICommand
{
    virtual void ToString() = 0; //dummy function to make abstract
};

class Update : ICommand
{
    public:
        ECommandType CommandType = ECT_Update;
        int UserID;
        int AttributeID;
};

class Authorize : ICommand
{
    public:
        ECommandType CommandType = ECT_Authorize;
        string Username;
        string Password;
};

#endif // COMMANDS_H
