#include "Enums.h"
#include "QApplicationGlobal.h"
#include "UserDAO.h"
#include <QSqlQuery>
#include <QSqlError>
#include <string>



ECommandResult UserDataAccessObject::Auth(QString username, QString password)
{
    if (!DATABASE.isOpen())
    {
        qWarning("Error: connection with database failed");
        return ECommandResult::ECR_FAILURE;
    }

    QSqlQuery query(DATABASE);
    query.prepare("SELECT Password FROM User WHERE Username = :username");
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qWarning() << "authenticate() ERROR: " << query.lastError().text();
        return ECommandResult::ECR_FAILURE;
    }

    if (query.next())
    {
        QString storedPassword = query.value(0).toString(); // Gets the password from the query

        // Compares the input password with the one stored in database
        // Please note this is a simple comparison, for real applications consider using a hashed password
        if (password == storedPassword)
        {
            return ECommandResult::ECR_SUCCESS; // Authenticated
        }
    }

    return ECommandResult::ECR_FAILURE; // Not authenticated

}
