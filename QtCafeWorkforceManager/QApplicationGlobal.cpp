#include "QApplicationGlobal.h"


// Define the static member of QApplicationGlobal
int QApplicationGlobal::CurrentUserID;
QString QApplicationGlobal::CurrentUsername;
QSqlDatabase QApplicationGlobal::CafeDB;

QApplicationGlobal::QApplicationGlobal(int &argc, char **argv) : QApplication(argc, argv)
{
    CafeDB = QSqlDatabase::addDatabase("QSQLITE");

    if (!CafeDB.open())
    {
        qDebug() << "Error: connection with database failed on init";
    }
    else
    {
        qDebug() << "Database: connection ok on init";
    }
}
