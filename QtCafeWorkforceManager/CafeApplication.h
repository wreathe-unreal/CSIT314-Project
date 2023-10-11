#ifndef CAFEAPPLICATION_H
#define CAFEAPPLICATION_H

#include "UserTypes.h"

#include <QApplication>


class CafeAplication : public QApplication
{
    vector<User*> Users;
    vector<Shift> Shifts;
};

#endif // CAFEAPPLICATION_H
