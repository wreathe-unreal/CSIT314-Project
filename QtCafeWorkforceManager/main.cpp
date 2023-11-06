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

    qDebug() << QDir::currentPath();

    QApplicationGlobal a(argc, argv);
    QApplicationGlobal::setStyle(QStyleFactory::create("Fusion"));

    //begin unit tests
    QString appDirPath = QApplication::applicationDirPath();

    // For the test database
    QString TestDBPath = QDir(appDirPath).filePath("../QtCafeWorkforceManager/TestDB.db");
    QApplicationGlobal::CafeDB.setDatabaseName(TestDBPath);


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

    // For the main database
    QString MainDBPath = QDir(appDirPath).filePath("../QtCafeWorkforceManager/CafeDB.db");
    QApplicationGlobal::CafeDB.setDatabaseName(MainDBPath);
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
