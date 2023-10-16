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
};

QString User::ToJSON()
{
    QJsonObject jsonObject;
    jsonObject["userID"] = QString::number(this->getUserID());
    jsonObject["username"] = QString(getUsername());
    jsonObject["EUP"] = QString::number(this->getEUP());
    jsonObject["ESR"] = QString::number(this->getESR());
    jsonObject["maxSlots"] = QString::number(this->getMaxSlots());

    QJsonDocument jsonDoc(jsonObject);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);
    return jsonString;
}
