#include <QString>
#include <string>
#include <QDebug>

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

class Update : public ICommand
{
    public:
        ECommandType CommandType = ECT_Update;
        int UserID;
        int AttributeID;
};

class Authorize : public ICommand
{
    public:
        ECommandType CommandType = ECT_Authorize;
        QString Username;
        QString Password;
        virtual void ToString(){ qDebug() << Username.toStdString() << Password.toStdString(); };
};

#endif // COMMANDS_H
