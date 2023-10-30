#include "Slot.h"


void Slot::setSlotID(int slotID)
{
    this->SlotID = slotID;
}


int Slot::getSlotID()
{
    return this->SlotID;
}

void Slot::setDate(QDate newSlotDate)
{
    this->Date = newSlotDate;
}



QDate Slot::getDate()
{
    return this->Date;
}


QTime Slot::getStartTime()
{
    return StartTime;
}

QTime Slot::getEndTime()
{
    return EndTime;
}
