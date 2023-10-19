#include "Enums.h"
#include "QApplicationGlobal.h"
#include "UserDAO.h"
#include <QSqlQuery>
#include "NewUser.h"
#include <QVector.h>
#include "Slot.h"
#include "User.h"
#include <QSqlError>
#include <string>
#include <QJsonObject>


class Slot;

EUserProfile UserDataAccessObject::Authorize(QString username, QString password)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
        return EUserProfile::EUP_CafeStaff;
    }

    bool bActive;
    QSqlQuery query(DATABASE);
    query.prepare("SELECT Password FROM User WHERE Username = :username"); //needs sanitize implementation
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qWarning() << "authenticate() ERROR FINDING USER: " << query.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return EUserProfile::EUP_CafeStaff;
    }

    if (query.next())
    {
        QString storedPassword = query.value(0).toString(); // Gets the password from the query

        // Compares the input password with the one stored in database
        if (password == storedPassword)
        {

            QSqlQuery queryActive(DATABASE);
            queryActive.prepare("SELECT bActive FROM User WHERE Username = :username");
            queryActive.bindValue(":username", username);

            if(!queryActive.exec())
            {
                qWarning() << "ERROR GETTING bACTIVE: " << queryActive.lastError().text();
                this->Result = EDatabaseResult::EDR_FAILURE;
                return EUserProfile::EUP_CafeStaff;
            }

            if(queryActive.next())
            {
                bActive = queryActive.value(0).toBool();

                if(!bActive)
                {
                    this->Result = EDatabaseResult::EDR_FAILURE;
                    return EUserProfile::EUP_CafeStaff;
                }

                //query to get EUP info
                QSqlQuery query2(DATABASE);
                query2.prepare("SELECT EUP FROM User WHERE Username = :username");
                query2.bindValue(":username", username);

                if (!query2.exec())
                {
                    qWarning() << "ERROR GETTING EUP: " << query.lastError().text();
                    this->Result = EDatabaseResult::EDR_FAILURE;
                    return EUserProfile::EUP_CafeStaff;
                }

                if (query2.next()) // Position query on the first (and hopefully only) result record
                {

                    //set global Username variable
                    QApplicationGlobal::CurrentUsername = username.toStdString();
                    this->Result = EDatabaseResult::EDR_SUCCESS;
                    return static_cast<EUserProfile>(query2.value(0).toInt()); // Authenticated
                }
            }
        }
    }

    this->Result = EDatabaseResult::EDR_FAILURE;
    return EUserProfile::EUP_CafeStaff;

}


QVector<User> UserDataAccessObject::GetByEUP(EUserProfile profile)
{
    int eup = EUserProfileToInt(profile);

    QVector<User> users; // Vector to store the retrieved User objects

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return users; // Return the empty vector
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE EUP = :eup");
    query.bindValue(":eup", eup);

    if (query.exec())
    {
        while (query.next())
        {
            User user;
            user.UserID = query.value("UserID").toInt();
            user.Username = query.value("Username").toString();
            user.Password = query.value("Password").toString();
            user.EUP = query.value("EUP").toInt();
            user.ESR = query.value("ESR").toInt();
            user.MaxSlots = query.value("MaxSlots").toInt();
            user.bActive = query.value("bActive").toBool();

            users.push_back(user);
        }
    }
    else
    {
        qWarning() << "getUsersByEUP() ERROR: " << query.lastError().text();
    }

    return users;
}

QVector<User> UserDataAccessObject::GetByESR(EStaffRole role)
{
    int esr = EStaffRoleToInt(role);

    QVector<User> users; // Vector to store the retrieved User objects

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return users; // Return the empty vector
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE ESR = :esr");
    query.bindValue(":esr", esr);

    if (query.exec())
    {
        while (query.next())
        {
            User user;
            user.UserID = query.value("UserID").toInt();
            user.Username = query.value("Username").toString();
            user.Password = query.value("Password").toString();
            user.EUP = query.value("EUP").toInt();
            user.ESR = query.value("ESR").toInt();
            user.MaxSlots = query.value("MaxSlots").toInt();
            user.bActive = query.value("bActive").toBool();

            users.push_back(user);
        }
    }
    else
    {
        qWarning() << "getUsersByESR() ERROR: " << query.lastError().text();
    }

    return users;
}

int UserDataAccessObject::GetMaxSlots(std::string username)
{
    int maxSlots = -1; // Initialized to -1 to indicate that the value wasn't found

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return maxSlots;
    }

    QSqlQuery query;
    query.prepare("SELECT MaxSlots FROM User WHERE Username = :username");
    query.bindValue(":username", QString::fromStdString(username));

    if (query.exec())
    {
        if (query.next())
        {
            maxSlots = query.value(0).toInt(); // Gets the MaxSlots value from the query
        }
    }
    else
    {
        qWarning() << "GetUserMaxSlots() ERROR: " << query.lastError().text();
    }

    return maxSlots;
}

EStaffRole UserDataAccessObject::GetESR(std::string username)
{
    EStaffRole esr = EStaffRole::ESR_NonStaff;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return esr;
    }

    QSqlQuery query;
    query.prepare("SELECT ESR FROM User WHERE Username = :username");
    query.bindValue(":username", QString::fromStdString(username));

    if (query.exec())
    {
        if (query.next())
        {
            esr = static_cast<EStaffRole>(query.value(0).toInt()); // Gets the ESR value from the query and casts it to the enum type
        }
    }
    else
    {
        qWarning() << "GetUserESP() ERROR: " << query.lastError().text();
    }

    return esr;
}


EUserProfile UserDataAccessObject::GetEUP(std::string username)
{
    EUserProfile eup = EUserProfile::EUP_CafeStaff; // Assuming you have a DEFAULT_VALUE or similar in your EStaffRole enum

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return eup;
    }

    QSqlQuery query;
    query.prepare("SELECT EUP FROM User WHERE Username = :username");
    query.bindValue(":username", QString::fromStdString(username));

    if (query.exec())
    {
        if (query.next())
        {
            eup = static_cast<EUserProfile>(query.value(0).toInt()); // Gets the ESR value from the query and casts it to the enum type
        }
    }
    else
    {
        qWarning() << "GetUserEUP() ERROR: " << query.lastError().text();
    }

    return eup;
}

User UserDataAccessObject::GetUser(const std::string& username)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return User(); // Returning an empty/default User object
    }

    QSqlQuery query;
    query.prepare("SELECT UserID, Username, Password, EUP, ESR, MaxSlots FROM User WHERE Username = :username");
    query.bindValue(":username", QString::fromStdString(username));

    if (query.exec())
    {
        if (query.next())
        {
            User user;

            // Assuming you have public or friend access, or setters for these members in the User class
            user.UserID = query.value(0).toInt();
            user.Username = query.value(1).toString();
            user.Password = query.value(2).toString();
            user.EUP = query.value(3).toInt();
            user.ESR = query.value(4).toInt();
            user.MaxSlots = query.value(5).toInt();

            return user;
        }
    }
    else
    {
        qWarning() << "GetUser() ERROR: " << query.lastError().text();
    }

    return User(); // Return a default User object if the username is not found or there's an error
}

void UserDataAccessObject::Insert(NewUser newUser)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Check if the username already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM User WHERE Username = :username");
    queryCheck.bindValue(":username", newUser.Username);

    if (queryCheck.exec())
    {
        if (queryCheck.next() && queryCheck.value(0).toInt() > 0)
        {
            qDebug() << "Username already exists.";
            this->Result = EDatabaseResult::EDR_FAILURE;
        }
    }
    else
    {
        qWarning() << "Check username query failed: " << queryCheck.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Insert the new user
    QSqlQuery queryInsert;
    queryInsert.prepare("INSERT INTO User (Username, Password, EUP, ESR, MaxSlots, bActive) VALUES (:username, :password, :eup, :esr, :maxslots, :active)");
    queryInsert.bindValue(":username", newUser.Username);
    queryInsert.bindValue(":password", newUser.Password);
    queryInsert.bindValue(":eup", newUser.EUP);
    queryInsert.bindValue(":esr", newUser.ESR);
    queryInsert.bindValue(":maxslots", 0);
    queryInsert.bindValue(":active", 1);

    if (queryInsert.exec())
    {
        this->Result = EDatabaseResult::EDR_SUCCESS;
    }
    else
    {
        qWarning() << "Insert user failed: " << queryInsert.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }
}


void UserDataAccessObject::UpdateOrInsert(User user)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Check if the user already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM User WHERE Username = :username");
    queryCheck.bindValue(":username", user.Username);

    if (queryCheck.exec())
    {
        if (queryCheck.next() && queryCheck.value(0).toInt() > 0)
        {
            // User exists, proceed with update
            QSqlQuery queryUpdate;
            queryUpdate.prepare("UPDATE User SET Password = :password, EUP = :eup, ESR = :esr, MaxSlots = :maxslots, bActive = :active WHERE Username = :username");
            queryUpdate.bindValue(":username", user.Username);
            queryUpdate.bindValue(":password", user.Password);
            queryUpdate.bindValue(":eup", user.EUP);
            queryUpdate.bindValue(":esr", user.ESR);
            queryUpdate.bindValue(":maxslots", user.MaxSlots);
            queryUpdate.bindValue(":active", user.bActive);

            if (queryUpdate.exec())
            {
                this->Result = EDatabaseResult::EDR_SUCCESS;
            }
            else
            {
                qWarning() << "Update user failed: " << queryUpdate.lastError().text();
                this->Result = EDatabaseResult::EDR_FAILURE;
            }
        }
        else
        {
            // User does not exist, proceed with insertion
            QSqlQuery queryInsert;
            queryInsert.prepare("INSERT INTO User (Username, Password, EUP, ESR, MaxSlots, bActive) VALUES (:username, :password, :eup, :esr, :maxslots, :active)");
            queryInsert.bindValue(":username", user.Username);
            queryInsert.bindValue(":password", user.Password);
            queryInsert.bindValue(":eup", user.EUP);
            queryInsert.bindValue(":esr", user.ESR);
            queryInsert.bindValue(":maxslots", user.MaxSlots);
            queryInsert.bindValue(":active", user.bActive);

            if (queryInsert.exec())
            {
                this->Result = EDatabaseResult::EDR_SUCCESS;
            }
            else
            {
                qWarning() << "Insert user failed: " << queryInsert.lastError().text();
                this->Result = EDatabaseResult::EDR_FAILURE;
            }
        }
    }
    else
    {
        qWarning() << "Check user query failed: " << queryCheck.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }
}

void UserDataAccessObject::SetMaxSlots(const std::string username, int maxSlots)
{
    if(!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Check if the user already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM User WHERE Username = :username");
    queryCheck.bindValue(":username", QString::fromStdString(username));

    if (queryCheck.exec())
    {
        if (queryCheck.next() && queryCheck.value(0).toInt() > 0)
        {
            // User exists, proceed with updating the MaxSlots column
            QSqlQuery queryUpdate;
            queryUpdate.prepare("UPDATE User SET MaxSlots = :maxslots WHERE Username = :username");
            queryUpdate.bindValue(":username", QString::fromStdString(username));
            queryUpdate.bindValue(":maxslots", maxSlots);

            if (queryUpdate.exec())
            {
                this->Result = EDatabaseResult::EDR_SUCCESS;
            }
            else
            {
                qWarning() << "Update MaxSlots failed: " << queryUpdate.lastError().text();
                this->Result = EDatabaseResult::EDR_FAILURE;
            }
        }
        else
        {
            qWarning("Error: User not found");
            this->Result = EDatabaseResult::EDR_FAILURE;
        }
    }
    else
    {
        qWarning() << "Check user query failed: " << queryCheck.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }
}

bool UserDataAccessObject::GetbActive(std::string username)
{   if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    QSqlQuery query;
    query.prepare("SELECT EUP FROM User WHERE Username = :username");
    query.bindValue(":username", QString::fromStdString(username));

    if (query.exec())
    {
        if (query.next())
        {
            this->Result = EDatabaseResult::EDR_SUCCESS;
            return query.value(0).toBool();
        }
    }
    else
    {
        qWarning() << "GetUserEUP() ERROR: " << query.lastError().text();
        return false;
    }
    return false;
}

void UserDataAccessObject::SuspendUser(std::string username)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    QSqlQuery query;
    query.prepare("SELECT EUP FROM User WHERE Username = :username");
    query.bindValue(":username", QString::fromStdString(username));

    if (query.exec())
    {
        if (query.next())
        {
            // User exists, proceed with updating the EUP column
            QSqlQuery queryUpdate;
            queryUpdate.prepare("UPDATE User SET bActive = :active WHERE Username = :username");
            queryUpdate.bindValue(":active", 0);

            this->Result = EDatabaseResult::EDR_SUCCESS;
        }
    }
    else
    {
        qWarning() << "GetUserEUP() ERROR: " << query.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }
}

void UserDataAccessObject::SetEUP(std::string username, EUserProfile profile)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Check if the user already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM User WHERE Username = :username");
    queryCheck.bindValue(":username", QString::fromStdString(username));

    if (queryCheck.exec())
    {
        if (queryCheck.next() && queryCheck.value(0).toInt() > 0)
        {
            // User exists, proceed with updating the EUP column
            QSqlQuery queryUpdate;
            queryUpdate.prepare("UPDATE User SET EUP = :eup WHERE Username = :username");
            queryUpdate.bindValue(":username", QString::fromStdString(username));
            queryUpdate.bindValue(":eup", static_cast<int>(profile));

            if (queryUpdate.exec())
            {
                this->Result = EDatabaseResult::EDR_SUCCESS;
            }
            else
            {
                qWarning() << "Update EUP failed: " << queryUpdate.lastError().text();
                this->Result = EDatabaseResult::EDR_FAILURE;
            }
        }
        else
        {
            qWarning("Error: User not found");
            this->Result = EDatabaseResult::EDR_FAILURE;
        }
    }
    else
    {
        qWarning() << "Check user query failed: " << queryCheck.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }
}


void UserDataAccessObject::SetESR(std::string username, EStaffRole role)
{

    if (!DATABASE.open())
    {
        qDebug() << "Error: Unable to open the database.";
        this->Result = EDatabaseResult::EDR_SUCCESS;
    }

    QSqlQuery query;
    // Prepare SQL statement to update ESR for the given username
    query.prepare("UPDATE User SET ESR = :esr WHERE Username = :username");

    query.bindValue(":esr", static_cast<int>(role));
    query.bindValue(":username", QString::fromStdString(username));

    if (!query.exec())
    {
        qDebug() << "Error: Failed to update ESR. Error:" << query.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    if (query.numRowsAffected() == 0)
    {
        qDebug() << "No user found with the provided username.";
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
}

void UserDataAccessObject::Delete(std::string username)
{

    if (!DATABASE.open())
    {
        qDebug() << "Error: Unable to open the database.";
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    QSqlQuery query;

    // Prepare SQL statement to delete user with the given username
    query.prepare("DELETE FROM User WHERE Username = :username");

    query.bindValue(":username", QString::fromStdString(username));

    if (!query.exec())
    {
        qDebug() << "Error: Failed to delete user. Error:" << query.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    if (query.numRowsAffected() == 0)
    {
        qDebug() << "No user found with the provided username.";
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
}


QVector<Slot> UserDataAccessObject::GetSlotsByUser(std::string username)
{
    QVector<Slot> associatedSlots;

    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return associatedSlots; // Return empty QVector
    }

    QSqlQuery query;

    // First, get the UserID for the provided username from the User table
    query.prepare("SELECT UserID FROM User WHERE Username = ?");
    query.addBindValue(QString::fromStdString(username));
    if (!query.exec() || !query.next())
    {
        qWarning() << "Failed to execute User query or user not found:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return associatedSlots;
    }

    int userID = query.value(0).toInt();

    // Then, get the SlotIDs from the UserSlot table for the found UserID
    query.prepare("SELECT SlotID FROM UserSlot WHERE UserID = ?");
    query.addBindValue(userID);
    if (!query.exec()) {
        qWarning() << "Failed to execute UserSlot query:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return associatedSlots;
    }

    while (query.next())
    {
        int slotID = query.value(0).toInt();

        // Then, for each SlotID, get the Slot details from the Slot table
        QSqlQuery slotQuery;
        slotQuery.prepare("SELECT * FROM Slot WHERE SlotID = ?");
        slotQuery.addBindValue(slotID);
        if (slotQuery.exec() && slotQuery.next()) {
            Slot slot;
            slot.setSlotID(slotQuery.value("SlotID").toInt());
            slot.setDate(QDate::fromString(slotQuery.value("SlotDate").toString(), "yyyy-MM-dd"));
            slot.setStartTime(QTime::fromString(slotQuery.value("SlotStart").toString(), "hh:mm:ss"));
            slot.setEndTime(QTime::fromString(slotQuery.value("SlotEnd").toString(), "hh:mm:ss"));
            slot.setMaxChefs(slotQuery.value("MaxChefs").toInt());
            slot.setCurChefs(slotQuery.value("CurChefs").toInt());
            slot.setMaxCashiers(slotQuery.value("MaxCashiers").toInt());
            slot.setCurCashiers(slotQuery.value("CurCashiers").toInt());
            slot.setMaxWaiters(slotQuery.value("MaxWaiters").toInt());
            slot.setCurWaiters(slotQuery.value("CurWaiters").toInt());

            associatedSlots.push_back(slot);
        }
        else
        {
            qWarning() << "Failed to execute Slot query or slot not found:" << slotQuery.lastError();
            this->Result = EDatabaseResult::EDR_FAILURE;
        }
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
    return associatedSlots;
}
