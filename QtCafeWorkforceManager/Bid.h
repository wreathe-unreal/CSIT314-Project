#ifndef BID_H
#define BID_H

#include <QDebug>
#include "Entity.h"

class Bid : public IEntity
{
    public:
        Bid(); // default constructor
        ~Bid(); // destructor
        Bid(int bidID, int userID, int slotID);
        // Getters
        int getBidID() const;
        int getSlotID() const;

        // Setters
        void setBidID(int bidID);
        void setSlotID(int slotID);

        int getUserID() const;
        void setUserID(int newUserID);

        int getEBS() const;
        void setEBS(int newEBS);

        int BidID;          // Unique identifier for the bid
        int UserID;
        int SlotID;        // ID of the shift for which the bid is made
        int EBS;
        virtual void ToString() override { qDebug() << QString::number(getBidID());}

};

#endif // BID_H
