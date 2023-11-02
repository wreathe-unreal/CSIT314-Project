#ifndef UNITTESTS_H
#define UNITTESTS_H

#include "Bid.h"
#include "Slot.h"
#include "User.h"



class UnitTests
{
    public:
    static QVector<User> InjectUsers;
    static QVector<Slot> InjectSlots;
    static QVector<Bid>  InjectBids;

    UnitTests();
    static bool Assert();
};

#endif // UNITTESTS_H