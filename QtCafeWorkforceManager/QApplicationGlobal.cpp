#include "QApplicationGlobal.h"


// Define the static member of QApplicationGlobal
std::string QApplicationGlobal::CurrentUsername;
QSqlDatabase QApplicationGlobal::CafeDB;
UserDataAccessObject QApplicationGlobal::UserDAO;
ShiftDataAccessObject QApplicationGlobal::ShiftDAO;
Controller* QApplicationGlobal::ControllerPtr = nullptr;

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

Controller* QApplicationGlobal::GetController()
{
    if(!ControllerPtr)
    {
        ControllerPtr = new Controller();
    }
    return ControllerPtr;
}

void QApplicationGlobal::SafeDeleteController()
{
    if(ControllerPtr != nullptr)
    {
        delete ControllerPtr;
        ControllerPtr = nullptr;
    }
};

