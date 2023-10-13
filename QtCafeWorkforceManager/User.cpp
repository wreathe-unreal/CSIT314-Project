#include "Entity.h"
#include "User.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

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
