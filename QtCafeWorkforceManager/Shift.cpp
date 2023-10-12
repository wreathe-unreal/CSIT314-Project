#include "Shift.h"


int Shift::getNumChefs() const
{
    return NumChefs;
}

void Shift::setNumChefs(int newNumChefs)
{
    NumChefs = newNumChefs;
}

int Shift::getShiftID() const
{
    return ShiftID;
}

QDate Shift::getShiftDate() const
{
    return ShiftDate;
}

void Shift::setShiftDate(const QDate &newShiftDate)
{
    ShiftDate = newShiftDate;
}

int Shift::getShiftNumber() const
{
    return ShiftNumber;
}

void Shift::setShiftNumber(int newShiftNumber)
{
    ShiftNumber = newShiftNumber;
}

bool Shift::getbFull() const
{
    return bFull;
}

void Shift::setbFull(bool newBFull)
{
    bFull = newBFull;
}

int Shift::getCurChefs() const
{
    return CurChefs;
}

void Shift::setCurChefs(int newCurChefs)
{
    CurChefs = newCurChefs;
}

int Shift::getNumCashiers() const
{
    return NumCashiers;
}

void Shift::setNumCashiers(int newNumCashiers)
{
    NumCashiers = newNumCashiers;
}

int Shift::getCurCashiers() const
{
    return CurCashiers;
}

void Shift::setCurCashiers(int newCurCashiers)
{
    CurCashiers = newCurCashiers;
}

int Shift::getNumWaiters() const
{
    return NumWaiters;
}

void Shift::setNumWaiters(int newNumWaiters)
{
    NumWaiters = newNumWaiters;
}

int Shift::getCurWaiters() const
{
    return CurWaiters;
}

void Shift::setCurWaiters(int newCurWaiters)
{
    CurWaiters = newCurWaiters;
}

