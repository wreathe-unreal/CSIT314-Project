#include "Bid.h"

Bid::Bid()
{

}

Bid::~Bid()
{

}

Bid::Bid(int bidID, int userID, int slotID)
{
    this->BidID = bidID;
    this->UserID = userID;
    this->SlotID = slotID;
}

int Bid::getBidID() const
{
    return BidID;
}

int Bid::getSlotID() const
{
    return this->SlotID;
}

void Bid::setBidID(int bidID)
{
    this->BidID = bidID;
}

void Bid::setSlotID(int slotID)
{
    this->SlotID = slotID;
}

int Bid::getUserID() const
{
    return this->UserID;
}

void Bid::setUserID(int newUserID)
{
    this->UserID = newUserID;
}

int Bid::getEBS() const
{
    return this->EBS;
}

void Bid::setEBS(int newEBS)
{
    this->EBS = newEBS;
}
