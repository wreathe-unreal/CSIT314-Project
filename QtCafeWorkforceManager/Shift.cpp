#include "Shift.h"


int Shift::getMaxChefs() const
{
    return MaxChefs;
}


int Shift::getShiftID() const
{
    return ShiftID;
}


int Shift::getCurChefs() const
{
    return CurChefs;
}

void Shift::setCurChefs(int newCurChefs)
{
    CurChefs = newCurChefs;
}

int Shift::getMaxCashiers() const
{
    return MaxCashiers;
}

int Shift::getCurCashiers() const
{
    return CurCashiers;
}

void Shift::setCurCashiers(int newCurCashiers)
{
    CurCashiers = newCurCashiers;
}

int Shift::getMaxWaiters() const
{
    return MaxWaiters;
}


int Shift::getCurWaiters() const
{
    return CurWaiters;
}

void Shift::setCurWaiters(int newCurWaiters)
{
    CurWaiters = newCurWaiters;
}



bool Shift::isChefRoleFull() const
{
    return CurChefs == MaxChefs;
}


bool Shift::isWaiterRoleFull() const
{
    return CurWaiters == MaxWaiters;
}

bool Shift::isCashierRoleFull() const
{
    return CurCashiers == MaxCashiers;
}

bool Shift::isShiftFull() const
{
    return isChefRoleFull() && isWaiterRoleFull() && isCashierRoleFull();
}

QTime Shift::getStartTime() const
{
    return StartTime;
}

QTime Shift::getEndTime() const
{
    return EndTime;
}
