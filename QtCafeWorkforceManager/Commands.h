#include "Enums.h"
#include <QString>
#include <string>
#include <QDebug>

#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

using namespace std;

class ICommand
{
    public:    virtual ECommandType GetType() = 0;//dummy function to make abstract
    virtual ~ICommand(){};
};

class Authorize : public ICommand
{
    public:
        virtual ECommandType GetType() override { return ECT_Authorize; }
        virtual ~Authorize() override {};
        QString Username;
        QString Password;
};

#endif // COMMANDS_H
