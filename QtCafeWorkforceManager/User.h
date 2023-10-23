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

        QString getUsername() { return Username; }
        void setUsername(QString username);

        QString getPassword() const { return Password; }
        void setPassword(QString password);

        int getEUP() const { return EUP;}
        void setEUP(int eup);

        int getESR() const { return ESR; }
        void setESR(int esr);

        int getMaxSlots() const {  return MaxSlots; }
        void setMaxSlots(int maxSlots);

        bool getbActive() const { return bActive; }
        void setbActive(bool bIsActive) { this->bActive = bIsActive;}

        QString Username;
        QString Password;
        int EUP; // Enum value EUserProfile
        int ESR; // Enum value EStaffRole
        int MaxSlots;
        bool bActive;
        QString FullName;

        QString ToJSON();

        virtual void ToString() override { qDebug() << this->getUsername();}
        QString getFullName() const;
        void setFullName(QString newFullName);
};

#endif // USER_H
