#include "User.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

User::User(){};
User::~User(){}

void User::setUsername(QString username)
{
    this->Username = username;
}

void User::setPassword(QString password)
{
    this->Password = password;
}

void User::setEUP(int eup)
    {
    this->EUP = eup;
}

void User::setESR(int esr)
{
    this->ESR = esr;
}

void User::setMaxSlots(int maxSlots)
{
    this->MaxSlots = maxSlots;
}

QString User::getFullName() const
{
    return FullName;
}

void User::setFullName(QString newFullName)
{
    FullName = newFullName;
};
