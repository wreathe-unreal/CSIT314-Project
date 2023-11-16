// User.h
#ifndef USER_H
#define USER_H

#include "Entity.h"
#include "Response.h"
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

class Slot;

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

        int UserID;
        QString Username;
        QString Password;
        int EUP; // Enum value EUserProfile
        int ESR; // Enum value EStaffRole
        int MaxSlots;
        bool bActive;
        QString FullName;

        virtual void ToString() override { qDebug() << this->getUsername();}
        QString getFullName() const;
        void setFullName(QString newFullName);

        static Response<void> IsUserActive(QString username);
        static Response<void> Insert(User user);
        static Response<QVector<User>> SearchByESR(EStaffRole role);
        static Response<QVector<User>> SearchByEUP(EUserProfile profile);
        static Response<EUserProfile> Authorize(QString username, QString password);
        static Response<int> GetMaxSlots(std::string username);
        static Response<EUserProfile> GetEUP(QString username);
        static Response<EStaffRole> GetESR(QString username);
        static Response<User> GetUser(QString username);
        static Response<User> GetUser(int userID);
        static Response<void> UpdateOrInsert(User user, QString usernameBeforeUpdate);
        static Response<void> SetMaxSlots(QString username, int maxSlots);
        static Response<void> SetEUP(QString username, EUserProfile profile);
        static Response<void> SetESR(QString username, EStaffRole role);
        static Response<void> Delete(int userid);
        static Response<QVector<User>> GetUsers();
        static Response<QString> GetName(QString username);
        static Response<void> SetName(QString username, QString newName);
        static Response<QVector<Slot>> GetSlotsByUser(int userid);
        static Response<bool> GetbActive(QString username);
        static Response<void> SuspendUser(QString username);
        static Response<int> GetUserID(QString username);
        static Response<QVector<User>> SearchByUsername(QString username);
};

#endif // USER_H
