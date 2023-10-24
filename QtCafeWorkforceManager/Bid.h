#ifndef BID_H
#define BID_H

#include "Entity.h"

#include <string>

class Bid : public IEntity
{
    public:
        Bid();  // default constructor
        ~Bid(); // destructor

        // Getters
        int getBidID() const { return BidID;}
        int getShiftID() const {return ShiftID;}

        // Setters
        void setBidID(int bidID);
        void setShiftID(int shiftID);

        int getUserID() const;
        void setUserID(int newUserID);

    private:
        int BidID;          // Unique identifier for the bid
        int UserID;
        int ShiftID;        // ID of the shift for which the bid is made
};

#endif // BID_H
