#include "AuthWindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "QApplicationGlobal.h"
#include "UnitTests.h"
#include <QStyleFactory>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplicationGlobal a(argc, argv);
    QApplicationGlobal::setStyle(QStyleFactory::create("Fusion"));

    //begin unit tests
    QString appDirPath = QApplication::applicationDirPath();

    // For the test database
    QString testDbPath = QDir(appDirPath).filePath("../QtCafeWorkforceManager/TestDB.db");
    QApplicationGlobal::CafeDB.setDatabaseName(testDbPath);

    // For the main database
    QString mainDbPath = QDir(appDirPath).filePath("../QtCafeWorkforceManager/CafeDB.db");
    QApplicationGlobal::CafeDB.setDatabaseName(mainDbPath);

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
    QApplicationGlobal::CafeDB.open();
    if (!QApplicationGlobal::CafeDB.open())
    {
        qCritical() << "Failed to open main database";
        return -1; // Exit with an error code
    }
    AuthWindow w;
    w.show();

    //close db and close app
    return a.exec();
}
