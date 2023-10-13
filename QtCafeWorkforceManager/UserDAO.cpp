#include "Enums.h"
#include "QApplicationGlobal.h"
#include "UserDAO.h"
#include <QSqlQuery>
#include "Response.h"
#include <QSqlError>
#include <string>



Response UserDataAccessObject::Auth(QString username, QString password)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        QJsonObject jsonObj;
        jsonObj["foo"] = 5;
        return Response(ECommandResult::ECR_FAILURE, jsonObj);
    }

    QSqlQuery query(DATABASE);
    query.prepare("SELECT Password FROM User WHERE Username = :username"); //needs sanitize implementation
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qWarning() << "authenticate() ERROR: " << query.lastError().text();
        return Response(ECommandResult::ECR_FAILURE);
    }

    if (query.next())
    {
        QString storedPassword = query.value(0).toString(); // Gets the password from the query

        // Compares the input password with the one stored in database
        if (password == storedPassword)
        {
            QApplicationGlobal::CurrentUsername = username.toStdString();
            QSqlQuery query2(DATABASE);
            query2.prepare("SELECT EUP FROM User WHERE Username = :username");
            query2.bindValue(":username", username);
            QJsonObject jsonEUP;
            jsonEUP["EUP"] = query2.value(0).toInt();
            return Response(ECommandResult::ECR_SUCCESS, jsonEUP);; // Authenticated
        }
    }

    return Response(ECommandResult::ECR_FAILURE); // Not authenticated

}
