#include "AuthWindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "QApplicationGlobal.h"
#include "UnitTests.h"
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplicationGlobal a(argc, argv);
    QApplicationGlobal::setStyle(QStyleFactory::create("Fusion"));

    //begin unit tests
    QApplicationGlobal::CafeDB.setDatabaseName("../QtCafeWorkforceManager/TestDB.db");
    QApplicationGlobal::CafeDB.open();
    if (!QApplicationGlobal::CafeDB.open())
    {
        qCritical() << "Failed to open test database";
        return -1; // Exit with an error code
    }
    //assert unit tests
    if(UnitTests::Assert() == false)
    {
         qCritical() << "Unit tests failed";
        return a.exec();
    }
    QApplicationGlobal::CafeDB.close();
    //end unit tests

    //continue with program execution
    //change from testing TestDB.db to deployment CafeDB.db
    QApplicationGlobal::CafeDB.setDatabaseName("../QtCafeWorkforceManager/CafeDB.db");
    QApplicationGlobal::CafeDB.open();
    if (!QApplicationGlobal::CafeDB.open())
    {
        qCritical() << "Failed to open main database";
        return -1; // Exit with an error code
    }
    AuthWindow w;
    w.setStyleSheet("AuthWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
    w.show();

    //close db and close app
    return a.exec();
}
