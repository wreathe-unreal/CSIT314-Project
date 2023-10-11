#include "mainwindow.h"
#include <QApplication>
#include "UserTypes.h"
#include <QDebug>
#include "Enums.h"

int main(int argc, char *argv[])
{
    qputenv("QT_ASSUME_STDERR_HAS_CONSOLE", "1");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
