#include "mainwindow.h"
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
    MainWindow w;
    w.show();
    return a.exec();
}
