#include "AuthWindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "QApplicationGlobal.h"

int main(int argc, char *argv[])
{
    QApplicationGlobal a(argc, argv);
    AuthWindow w;
    w.show();
    return a.exec();
}
