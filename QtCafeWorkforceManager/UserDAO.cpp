#include "Enums.h"
#include "QApplicationGlobal.h"
#include "UserDAO.h"
#include <QSqlQuery>
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
        qDebug() << "authenticate() ERROR FINDING USER: " << query.lastError().text();
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
            //query to get EUP info
            QSqlQuery query2(DATABASE);
            query2.prepare("SELECT EUP FROM User WHERE Username = :username");
            query2.bindValue(":username", username);

            if (!query2.exec())
            {
                qDebug() << "ERROR GETTING EUP: " << query.lastError().text();
                qWarning() << "ERROR GETTING EUP: " << query.lastError().text();
                this->Result = EDatabaseResult::EDR_FAILURE;
                return EUserProfile::EUP_CafeStaff;
            }

            if (query2.next()) // Position query on the first (and hopefully only) result record
            {
                //set global Username variable
                QApplicationGlobal::CurrentUsername = username;
                this->Result = EDatabaseResult::EDR_SUCCESS;
                return static_cast<EUserProfile>(query2.value(0).toInt()); // Authenticated
            }
        }
    }

    this->Result = EDatabaseResult::EDR_FAILURE;
    return EUserProfile::EUP_CafeStaff;

}


QVector<User> UserDataAccessObject::SearchByEUP(EUserProfile profile)
{
    int eup = EUserProfileToInt(profile);

    QVector<User> users; // Vector to store the retrieved User objects

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QApplicationGlobal::UserDAO.Result = EDatabaseResult::EDR_FAILURE;
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
            user.Username = query.value("Username").toString();
            user.Password = query.value("Password").toString();
            user.EUP = query.value("EUP").toInt();
            user.ESR = query.value("ESR").toInt();
            user.MaxSlots = query.value("MaxSlots").toInt();
            user.bActive = query.value("bActive").toBool();
            user.FullName = query.value("FullName").toString();

            users.push_back(user);
        }
    }
    else
    {
        qWarning() << "getUsersByEUP() ERROR: " << query.lastError().text();
        QApplicationGlobal::UserDAO.Result = EDatabaseResult::EDR_FAILURE;

    }
    QApplicationGlobal::UserDAO.Result = EDatabaseResult::EDR_SUCCESS;
    return users;
}

QVector<User> UserDataAccessObject::SearchByESR(EStaffRole role)
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
            user.Username = query.value("Username").toString();
            user.Password = query.value("Password").toString();
            user.EUP = query.value("EUP").toInt();
            user.ESR = query.value("ESR").toInt();
            user.MaxSlots = query.value("MaxSlots").toInt();
            user.bActive = query.value("bActive").toBool();
            user.FullName = query.value("FullName").toString();

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

EUserProfile UserDataAccessObject::GetEUP(QString username)
{
    EUserProfile eup = EUserProfile::EUP_CafeStaff;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return eup;
    }

    QSqlQuery query;
    query.prepare("SELECT EUP FROM User WHERE Username = :username");
    query.bindValue(":username", username);

    if (query.exec())
    {
        if (query.next())
        {
            eup = static_cast<EUserProfile>(query.value(0).toInt()); // Gets the ESR value from the query and casts it to the enum type
        }
    }
    else
    {
        qWarning() << "GetUserESP() ERROR: " << query.lastError().text();
    }

    return eup;
}

EStaffRole UserDataAccessObject::GetESR(QString username)
{
    EStaffRole esr = EStaffRole::ESR_NonStaff;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return esr;
    }

    QSqlQuery query;
    query.prepare("SELECT ESR FROM User WHERE Username = :username");
    query.bindValue(":username", username);

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


User UserDataAccessObject::GetUser(QString username)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return User(); // Returning an empty/default User object
    }

    QSqlQuery query;
    query.prepare("SELECT Username, Password, EUP, ESR, MaxSlots, bActive, FullName FROM User WHERE Username = :username");
    query.bindValue(":username", username);

    if (query.exec())
    {
        if (query.next())
        {
            User user;

            // Assuming you have public or friend access, or setters for these members in the User class
            user.Username = query.value(0).toString();
            user.Password = query.value(1).toString();
            user.EUP = query.value(2).toInt();
            user.ESR = query.value(3).toInt();
            user.MaxSlots = query.value(4).toInt();
            user.bActive = query.value(5).toBool();
            user.FullName = query.value(6).toString();

            this->Result = EDatabaseResult::EDR_SUCCESS;
            return user;
        }
    }
    else
    {
        qWarning() << "GetUser() ERROR: " << query.lastError().text();
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    this->Result = EDatabaseResult::EDR_FAILURE;
    return User(); // Return a default User object if the username is not found or there's an error
}

void UserDataAccessObject::IsUserActive(QString username)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
        return;
    }

    QSqlQuery query(DATABASE);
    query.prepare("SELECT bActive FROM User WHERE Username = :username");
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qDebug() << "IsUserActive() ERROR FINDING USER: " << query.lastError().text();
        qWarning() << "IsUserActive() ERROR FINDING USER: " << query.lastError().text();\
        this->Result = EDatabaseResult::EDR_FAILURE;
        return;
    }

    if(query.next())
    {
        bool bActive = query.value(0).toBool();
        if(bActive)
        {
            this->Result = EDatabaseResult::EDR_SUCCESS;
            return;
        }
    }

    this->Result = EDatabaseResult::EDR_FAILURE;
    return;
}

void UserDataAccessObject::Insert(User user)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Check if the username already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM User WHERE Username = :username");
    queryCheck.bindValue(":username", user.Username);

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
    queryInsert.prepare("INSERT INTO User (Username, Password, EUP, ESR, MaxSlots, bActive, FullName) VALUES (:username, :password, :eup, :esr, :maxslots, :active, :fullname)");
    queryInsert.bindValue(":username", user.Username);
    queryInsert.bindValue(":password", user.Password);
    queryInsert.bindValue(":eup", user.EUP);
    queryInsert.bindValue(":esr", user.ESR);
    queryInsert.bindValue(":maxslots", 0);
    queryInsert.bindValue(":active", user.bActive);
    queryInsert.bindValue(":fullname", user.FullName);

    //give a user 1 default workslot if they are a staff member
    if(user.EUP >= 2)
    {
        queryInsert.bindValue(":maxslots", 1);

    }
    if(user.EUP < 2)
    {
        queryInsert.bindValue(":maxslots", 0);

    }

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


void UserDataAccessObject::UpdateOrInsert(User user, QString usernameBeforeUpdate)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Check if the user already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM User WHERE Username = :username");
    queryCheck.bindValue(":username", usernameBeforeUpdate);

    if (queryCheck.exec())
    {
        if (queryCheck.next() && queryCheck.value(0).toInt() > 0)
        {
            // User exists, proceed with update
            QSqlQuery queryUpdate;
            queryUpdate.prepare("UPDATE User SET Username = :newUsername, Password = :password, EUP = :eup, ESR = :esr, MaxSlots = :maxslots, bActive = :active, FullName = :fullname WHERE Username = :username");
            queryUpdate.bindValue(":newUsername", user.Username);
            queryUpdate.bindValue(":username", usernameBeforeUpdate);
            queryUpdate.bindValue(":password", user.Password);
            queryUpdate.bindValue(":eup", user.EUP);
            queryUpdate.bindValue(":esr", user.ESR);
            queryUpdate.bindValue(":maxslots", user.MaxSlots);
            queryUpdate.bindValue(":active", user.bActive);
            queryUpdate.bindValue(":fullname", user.FullName);

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
            queryInsert.prepare("INSERT INTO User (Username, Password, EUP, ESR, MaxSlots, bActive, FullName) VALUES (:username, :password, :eup, :esr, :maxslots, :active, :fullname)");
            queryInsert.bindValue(":username", user.Username);
            queryInsert.bindValue(":password", user.Password);
            queryInsert.bindValue(":eup", user.EUP);
            queryInsert.bindValue(":esr", user.ESR);
            queryInsert.bindValue(":maxslots", user.MaxSlots);
            queryInsert.bindValue(":active", user.bActive);
            queryInsert.bindValue(":fullname", user.FullName);

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

void UserDataAccessObject::SetMaxSlots(QString username, int maxSlots)
{
    if(!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE User SET MaxSlots = :maxslots WHERE Username = :username");
    queryUpdate.bindValue(":username", username);
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

int UserDataAccessObject::GetUserID(QString username)
{
    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return -1; // Return empty QVector
    }

    QSqlQuery query;

    // First, get the UserID for the provided username from the User table
    query.prepare("SELECT UserID FROM User WHERE Username = ?");
    query.addBindValue(username);
    if (!query.exec() || !query.next())
    {
        qWarning() << "Failed to execute User query or user not found:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return -1;
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
    int userID = query.value(0).toInt();
    return userID;
}

void UserDataAccessObject::SetEUP(QString username, EUserProfile profile)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    // Check if the user already exists
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM User WHERE Username = :username");
    queryCheck.bindValue(":username", username);

    if (queryCheck.exec())
    {
        if (queryCheck.next() && queryCheck.value(0).toInt() > 0)
        {
            // User exists, proceed with updating the EUP column
            QSqlQuery queryUpdate;
            queryUpdate.prepare("UPDATE User SET EUP = :eup WHERE Username = :username");
            queryUpdate.bindValue(":username", username);
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


void UserDataAccessObject::SetESR(QString username, EStaffRole role)
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
    query.bindValue(":username", username);

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

void UserDataAccessObject::Delete(QString username)
{

    if (!DATABASE.open())
    {
        qDebug() << "Error: Unable to open the database.";
        this->Result = EDatabaseResult::EDR_FAILURE;
    }

    QSqlQuery query;

    // Prepare SQL statement to delete user with the given username
    query.prepare("DELETE FROM User WHERE Username = :username");

    query.bindValue(":username", username);

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
    else
    {
        this->Result = EDatabaseResult::EDR_SUCCESS;
    }
}

QVector<User> UserDataAccessObject::GetUsers()
{
    QVector<User> users; // Vector to store the retrieved User objects

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        Result = EDatabaseResult::EDR_FAILURE;
        return users; // Return the empty vector
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM User");

    if (query.exec())
    {
        while (query.next())
        {
            User user;
            user.Username = query.value("Username").toString();
            user.Password = query.value("Password").toString();
            user.EUP = query.value("EUP").toInt();
            user.ESR = query.value("ESR").toInt();
            user.MaxSlots = query.value("MaxSlots").toInt();
            user.bActive = query.value("bActive").toBool();
            user.FullName = query.value("FullName").toString();

            users.push_back(user);
        }
    }
    else
    {
        Result = EDatabaseResult::EDR_FAILURE;
        qWarning() << "GetUsers() ERROR: " << query.lastError().text();
    }
    Result = EDatabaseResult::EDR_SUCCESS;
    return users;
}

QString UserDataAccessObject::GetName(QString username)
{
    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return ""; // Return empty QVector
    }

    QSqlQuery query;

    // First, get the UserID for the provided username from the User table
    query.prepare("SELECT FullName FROM User WHERE Username = ?");
    query.addBindValue(username);
    if (!query.exec() || !query.next())
    {
        qWarning() << "Failed to execute User query or user not found:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return "";
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
    return query.value(0).toString();
}

void UserDataAccessObject::SetName(QString username, QString newName)
{
    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return; // Return empty QVector
    }

    QSqlQuery query;

    // First, get the UserID for the provided username from the User table
    query.prepare("UPDATE User SET FullName = :name WHERE Username = :username");

    query.bindValue(":name", newName);
    query.bindValue(":username", username);
    if (!query.exec() || !query.next())
    {
        qWarning() << "Failed to execute query or user not found:" << query.lastError();
        this->Result = EDatabaseResult::EDR_FAILURE;
        return;
    }

    this->Result = EDatabaseResult::EDR_SUCCESS;
    return;
}

QVector<Slot> UserDataAccessObject::GetSlotsByUser(QString username)
{
    QVector<Slot> associatedSlots;

    int userID = this->GetUserID(username);

    QSqlQuery query;
    // Then, get the SlotIDs from the UserSlot table for the found UserID
    query.prepare("SELECT SlotID FROM UserSlot WHERE UserID = ?");
    query.addBindValue(userID);
    if (!query.exec())
    {
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
            slot.setDate(QDate::fromString(slotQuery.value("SlotDate").toString()));
            slot.setStartTime(QTime::fromString(slotQuery.value("SlotStart").toString()));
            slot.setEndTime(QTime::fromString(slotQuery.value("SlotEnd").toString()));
            slot.setCurChefs(slotQuery.value("CurChefs").toInt());
            slot.setCurCashiers(slotQuery.value("CurCashiers").toInt());
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
