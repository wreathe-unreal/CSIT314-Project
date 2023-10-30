#include "AuthWindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "QApplicationGlobal.h"
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplicationGlobal a(argc, argv);
    QApplicationGlobal::setStyle(QStyleFactory::create("Fusion"));
    AuthWindow w;
    w.setStyleSheet("AuthWindow {background-image: url(../QtCafeWorkforceManager/bg.png);}");
    w.show();
    return a.exec();
}
