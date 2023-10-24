﻿#include "Slot.h"


void Slot::setSlotID(int slotID)
{
    this->SlotID = slotID;
}


int Slot::getSlotID() const
{
    return SlotID;
}

void Slot::setDate(QDate newSlotDate)
{
    this->Date = newSlotDate;
}


int Slot::getCurChefs() const
{
    return CurChefs;
}

void Slot::setCurChefs(int newCurChefs)
{
    CurChefs = newCurChefs;
}



int Slot::getCurCashiers() const
{
    return CurCashiers;
}

void Slot::setCurCashiers(int newCurCashiers)
{
    CurCashiers = newCurCashiers;
}



int Slot::getCurWaiters() const
{
    return CurWaiters;
}

void Slot::setCurWaiters(int newCurWaiters)
{
    CurWaiters = newCurWaiters;
}

QDate Slot::getDate() const
{
    return this->Date;
}


bool Slot::isSlotFull() const
{
    return CurChefs >=1 && CurCashiers >= 1 && CurWaiters >= 1;
}

QTime Slot::getStartTime() const
{
    return StartTime;
}

QTime Slot::getEndTime() const
{
    return EndTime;
}