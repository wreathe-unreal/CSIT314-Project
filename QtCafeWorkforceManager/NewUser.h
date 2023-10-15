#ifndef NEWUSER_H
#define NEWUSER_H
// NewUser.h

#include <QString>
#include <QDebug>

class NewUser
{

public:
    NewUser(QString username, QString password, int eup, int esr)
    {
        this->Username = username;
        this->Password = password;
        this->EUP = eup;
        this->ESR = esr;
    }
    ~NewUser();

    QString Username;
    QString Password;
    int EUP; // Enum value EUserProfile
    int ESR; // Enum value EStaffRole

};

#endif // NEWUSER_H
