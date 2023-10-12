#include "Entity.h"
#include "qdebug.h"
#include <QString>


Entity::Entity(const QString& path)
{
    CafeDB = QSqlDatabase::addDatabase("QSQLITE");
    CafeDB.setDatabaseName(path);

    if (!CafeDB.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}
