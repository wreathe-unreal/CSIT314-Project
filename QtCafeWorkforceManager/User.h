// User.h
#ifndef USER_H
#define USER_H

#include "Entity.h"
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

class User : public IEntity
{

    public:
        User();
        ~User();

        int getUserID() { return UserID; }
        //no setter needed...auto-incremented

        QString getUsername() { return Username; }
        void setUsername(const QString &username);

        QString getPassword() const { return Password; }
        void setPassword(const QString &password);

        int getEUP() const { return EUP;}
        void setEUP(int eup);

        int getESR() const { return ESR; }
        void setESR(int esr);

        int getMaxSlots() const {  return MaxSlots; }
        void setMaxSlots(int maxSlots);

        int UserID;
        QString Username;
        QString Password;
        int EUP; // Enum value EUserProfile
        int ESR; // Enum value EStaffRole
        int MaxSlots;

        QString ToJSON();

        virtual void ToString() override { qDebug() << this->getUsername();}
};

#endif // USER_H
