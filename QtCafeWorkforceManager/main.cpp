#include "AuthWindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "QApplicationGlobal.h"

int main(int argc, char *argv[])
{
    QApplicationGlobal a(argc, argv);
    AuthWindow w;
    w.setStyleSheet("AuthWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
    w.show();
    return a.exec();
}
