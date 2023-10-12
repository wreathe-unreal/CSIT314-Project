#include "QApplicationGlobal.h"


// Define the static member of QApplicationGlobal
QSqlDatabase QApplicationGlobal::CafeDB;
UserDAO QApplicationGlobal::UserDataAccessObject;
ShiftDAO QApplicationGlobal::ShiftDataAccessObject;
BidDAO QApplicationGlobal::BidDataAccessObject;

QApplicationGlobal::QApplicationGlobal(int &argc, char **argv) : QApplication(argc, argv)
{

    CafeDB = QSqlDatabase::addDatabase("QSQLITE");
    CafeDB.setDatabaseName("../QtCafeWorkforceManager/CafeDB.db");

    if (!CafeDB.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}
QApplicationGlobal::~QApplicationGlobal(){};

