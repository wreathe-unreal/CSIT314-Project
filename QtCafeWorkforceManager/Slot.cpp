#include "Slot.h"


int Slot::getMaxChefs() const
{
    return MaxChefs;
}


int Slot::getSlotID() const
{
    return SlotID;
}


int Slot::getCurChefs() const
{
    return CurChefs;
}

void Slot::setCurChefs(int newCurChefs)
{
    CurChefs = newCurChefs;
}

int Slot::getMaxCashiers() const
{
    return MaxCashiers;
}

int Slot::getCurCashiers() const
{
    return CurCashiers;
}

void Slot::setCurCashiers(int newCurCashiers)
{
    CurCashiers = newCurCashiers;
}

int Slot::getMaxWaiters() const
{
    return MaxWaiters;
}


int Slot::getCurWaiters() const
{
    return CurWaiters;
}

void Slot::setCurWaiters(int newCurWaiters)
{
    CurWaiters = newCurWaiters;
}



bool Slot::isChefRoleFull() const
{
    return CurChefs == MaxChefs;
}


bool Slot::isWaiterRoleFull() const
{
    return CurWaiters == MaxWaiters;
}

bool Slot::isCashierRoleFull() const
{
    return CurCashiers == MaxCashiers;
}

bool Slot::isSlotFull() const
{
    return isChefRoleFull() && isWaiterRoleFull() && isCashierRoleFull();
}

QTime Slot::getStartTime() const
{
    return StartTime;
}

QTime Slot::getEndTime() const
{
    return EndTime;
}
