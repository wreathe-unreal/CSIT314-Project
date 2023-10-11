#include "AuthWindow.h"
#include <QApplication>
#include "UserTypes.h"
#include <QDebug>
#include <iostream>
#include "CSVSerializer.h"
#include "Enums.h"
#include "QApplicationGlobal.h"

int main(int argc, char *argv[])
{
    QApplicationGlobal a(argc, argv);
    AuthWindow w;
    w.show();
    return a.exec();
}
