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
        const std::string& getUsername() const { return Username; }
        int getShiftID() const {return ShiftID;}

        // Setters
        void setBidID(int bidID);
        void setUsername(const std::string& username);
        void setShiftID(int shiftID);

    private:
        int BidID;          // Unique identifier for the bid
        std::string Username; // Username of the user who made the bid
        int ShiftID;        // ID of the shift for which the bid is made
};

#endif // BID_H
