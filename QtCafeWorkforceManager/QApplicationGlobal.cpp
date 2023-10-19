#include "QApplicationGlobal.h"


// Define the static member of QApplicationGlobal
std::string QApplicationGlobal::CurrentUsername;
QSqlDatabase QApplicationGlobal::CafeDB;
UserDataAccessObject QApplicationGlobal::UserDAO;
SlotDataAccessObject QApplicationGlobal::SlotDAO;

QApplicationGlobal::QApplicationGlobal(int &argc, char **argv) : QApplication(argc, argv)
{
    CafeDB = QSqlDatabase::addDatabase("QSQLITE");
    CafeDB.setDatabaseName("../QtCafeWorkforceManager/CafeDB.db");

    if (!CafeDB.open())
    {
        qDebug() << "Error: connection with database failed on init";
    }
    else
    {
        qDebug() << "Database: connection ok on init";
    }
}
