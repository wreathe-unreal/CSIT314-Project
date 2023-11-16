#include "Response.h"
#include "Slot.h"
#include "User.h"
#include <QString>
#include "QApplicationGlobal.h"
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

Response<EUserProfile> User::Authorize(QString username, QString password)
{
    Response<User> userResponse = GetUser(username);
    Response<EUserProfile> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        response.Data = EUserProfile::EUP_CafeStaff;
    }

    QSqlQuery query(DATABASE);
    query.prepare("SELECT Password FROM User WHERE Username = :username"); //needs sanitize implementation
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qDebug() << "authenticate() ERROR FINDING USER: " << query.lastError().text();
        qWarning() << "authenticate() ERROR FINDING USER: " << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        response.Data = EUserProfile::EUP_CafeStaff;
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
                response.Result = EDatabaseResult::EDR_FAILURE;
                response.Data = EUserProfile::EUP_CafeStaff;
            }

            if (query2.next()) // Position query on the first (and hopefully only) result record
            {
                //set global Username variable
                QApplicationGlobal::CurrentUserID = userResponse.Data.UserID;
                QApplicationGlobal::CurrentUsername = username;
                response.Result = EDatabaseResult::EDR_SUCCESS;
                response.Data = static_cast<EUserProfile>(query2.value(0).toInt());
                return response; // Authenticated
            }
        }
    }
    return response;
}


Response<QVector<User>> User::SearchByEUP(EUserProfile profile)
{
    Response<QVector<User>> response;

    int eup = EUserProfileToInt(profile);


    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Return the empty vector
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

            response.Data.push_back(user);
        }
    }
    else
    {
        qWarning() << "getUsersByEUP() ERROR: " << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;

    }
    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<QVector<User>> User::SearchByESR(EStaffRole role)
{
    Response<QVector<User>> response;
    int esr = EStaffRoleToInt(role);

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
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

            response.Data.push_back(user);
        }
    }
    else
    {
        qWarning() << "getUsersByESR() ERROR: " << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }
    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<User> User::GetUser(int userID)
{
    Response<User> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Returning an empty/default User object
    }

    QSqlQuery query;
    query.prepare("SELECT UserID, Username, Password, EUP, ESR, MaxSlots, bActive, FullName FROM User WHERE UserID = :userid");
    query.bindValue(":userid", userID);

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
            user.bActive = query.value(6).toBool();
            user.FullName = query.value(7).toString();

            response.Result = EDatabaseResult::EDR_SUCCESS;
            response.Data = user;
            return response;
        }
    }
    else
    {
        qWarning() << "GetUser() ERROR: " << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    response.Result = EDatabaseResult::EDR_FAILURE;
    return response; // Return a default User object if the username is not found or there's an error
}

Response<User> User::GetUser(QString username)
{
    Response<User> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Returning an empty/default User object
    }

    QSqlQuery query;
    query.prepare("SELECT UserID, Username, Password, EUP, ESR, MaxSlots, bActive, FullName FROM User WHERE Username = :username");
    query.bindValue(":username", username);

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
            user.bActive = query.value(6).toBool();
            user.FullName = query.value(7).toString();

            response.Result = EDatabaseResult::EDR_SUCCESS;
            response.Data = user;
            return response;
        }
    }
    else
    {
        qWarning() << "GetUser() ERROR: " << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    response.Result = EDatabaseResult::EDR_FAILURE;
    return response; // Return a default User object if the username is not found or there's an error
}

Response<void> User::Insert(User user)
{
    Response<void> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
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
            response.Result = EDatabaseResult::EDR_FAILURE;
            return response;
        }
    }
    else
    {
        qWarning() << "Check username query failed: " << queryCheck.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
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
        response.Result = EDatabaseResult::EDR_SUCCESS;
        return response;
    }
    else
    {
        qWarning() << "Insert user failed: " << queryInsert.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }
}


Response<void> User::UpdateOrInsert(User user, QString usernameBeforeUpdate)
{
    Response<void> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
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
                response.Result = EDatabaseResult::EDR_SUCCESS;
                return response;
            }
            else
            {
                qWarning() << "Update user failed: " << queryUpdate.lastError().text();
                response.Result = EDatabaseResult::EDR_FAILURE;
                return response;
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
                response.Result = EDatabaseResult::EDR_SUCCESS;
                return response;
            }
            else
            {
                qWarning() << "Insert user failed: " << queryInsert.lastError().text();
                response.Result = EDatabaseResult::EDR_FAILURE;
                return response;
            }
        }
    }
    else
    {
        qWarning() << "Check user query failed: " << queryCheck.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }
    return response;

}

Response<void> User::SetMaxSlots(QString username, int maxSlots)
{
    Response<void> response;

    if(!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE User SET MaxSlots = :maxslots WHERE Username = :username");
    queryUpdate.bindValue(":username", username);
    queryUpdate.bindValue(":maxslots", maxSlots);

    if (queryUpdate.exec())
    {
        response.Result = EDatabaseResult::EDR_SUCCESS;
        return response;
    }
    else
    {
        qWarning() << "Update MaxSlots failed: " << queryUpdate.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }
    return response;
}

Response<void> User::SuspendUser(QString username)
{
    Response<void> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query;
    query.prepare("SELECT EUP FROM User WHERE Username = :username");
    query.bindValue(":username", username);

    if (query.exec())
    {
        if (query.next())
        {
            // User exists, proceed with updating the EUP column
            QSqlQuery queryUpdate;
            queryUpdate.prepare("UPDATE User SET bActive = :active WHERE Username = :username");
            queryUpdate.bindValue(":active", 0);

            response.Result = EDatabaseResult::EDR_SUCCESS;
            return response;
        }
    }
    else
    {
        qWarning() << "GetUserEUP() ERROR: " << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }
    return response;
}

Response<QVector<User>> User::SearchByUsername(QString username)
{
    Response<QVector<User>> response;

    if (!DATABASE.isOpen()) {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE Username LIKE :username");
    query.bindValue(":username", "%" + username + "%");

    if (query.exec())
    {
        QVector<User> users;
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
            user.FullName = query.value("FullName").toString();

            response.Data.push_back(user);
        }
        response.Result = EDatabaseResult::EDR_SUCCESS;
    }
    else {
        qWarning() << "User search query failed: " << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
    }

    return response;
}

Response<void> User::SetEUP(QString username, EUserProfile profile)
{
    Response<void> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
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
                response.Result = EDatabaseResult::EDR_SUCCESS;
                return response;
            }
            else
            {
                qWarning() << "Update EUP failed: " << queryUpdate.lastError().text();
                response.Result = EDatabaseResult::EDR_FAILURE;
                return response;
            }
        }
        else
        {
            qWarning("Error: User not found");
            response.Result = EDatabaseResult::EDR_FAILURE;
            return response;

        }
    }
    else
    {
        qWarning() << "Check user query failed: " << queryCheck.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
    }
    response.Result = EDatabaseResult::EDR_FAILURE;
    return response;
}


Response<void> User::SetESR(QString username, EStaffRole role)
{

    Response<void> response;

    if (!DATABASE.open())
    {
        qDebug() << "Error: Unable to open the database.";
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;

    }

    QSqlQuery query;
    // Prepare SQL statement to update ESR for the given username
    query.prepare("UPDATE User SET ESR = :esr WHERE Username = :username");

    query.bindValue(":esr", static_cast<int>(role));
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qDebug() << "Error: Failed to update ESR. Error:" << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    if (query.numRowsAffected() == 0)
    {
        qDebug() << "No user found with the provided username.";
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;

}

Response<void> User::Delete(int userid)
{
    Response<void> response;

    if (!DATABASE.open())
    {
        qDebug() << "Error: Unable to open the database.";
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    QSqlQuery query;

    // Prepare SQL statement to delete user with the given username
    query.prepare("DELETE FROM User WHERE UserID = :userid");

    query.bindValue(":userid", userid);

    if (!query.exec())
    {
        qDebug() << "Error: Failed to delete user. Error:" << query.lastError().text();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    if (query.numRowsAffected() == 0)
    {
        qDebug() << userid;
        qDebug() << "No user found with the provided username.";
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }
    else
    {
        response.Result = EDatabaseResult::EDR_SUCCESS;
        return response;
    }
}

Response<QVector<User>> User::GetUsers()
{
    Response<QVector<User>> response;

    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Return the empty vector
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM User");

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
            user.FullName = query.value("FullName").toString();

            response.Data.push_back(user);
        }
    }
    else
    {
        response.Result = EDatabaseResult::EDR_FAILURE;
        qWarning() << "GetUsers() ERROR: " << query.lastError().text();
        return response;
    }
    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<void> User::SetName(QString username, QString newName)
{
    Response<void> response;

    if (!DATABASE.isOpen()) {
        qWarning() << "Error: connection with database failed" << DATABASE.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response; // Return empty QVector
    }

    QSqlQuery query;

    // First, get the UserID for the provided username from the User table
    query.prepare("UPDATE User SET FullName = :name WHERE Username = :username");

    query.bindValue(":name", newName);
    query.bindValue(":username", username);
    if (!query.exec() || !query.next())
    {
        qWarning() << "Failed to execute query or user not found:" << query.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}

Response<QVector<Slot>> User::GetSlotsByUser(int userID)
{
    Response<QVector<Slot>> response;

    QSqlQuery query;
    // Get the SlotIDs from the Bid table where EBS = 1 for the given UserID
    query.prepare("SELECT SlotID FROM Bid WHERE UserID = ? AND EBS = 1");
    query.addBindValue(userID);
    if (!query.exec())
    {
        qWarning() << "Failed to execute Bid query:" << query.lastError();
        response.Result = EDatabaseResult::EDR_FAILURE;
        return response;
    }

    while (query.next())
    {
        int slotID = query.value(0).toInt();

        // Use GetSlot function to get the Slot details for each SlotID
        Response<Slot> slotResponse = GetSlotController::Invoke(slotID);
        if(slotResponse.Result == EDatabaseResult::EDR_SUCCESS)
        {
            response.Data.push_back(slotResponse.Data);
        }
        else
        {
            qWarning() << "Failed to get slot details for SlotID:" << slotID;
            response.Result = EDatabaseResult::EDR_FAILURE;
            return response;
        }
    }

    response.Result = EDatabaseResult::EDR_SUCCESS;
    return response;
}
