#ifndef BIDDAO_H
#define BIDDAO_H
#include "Enums.h"
#include "Bid.h"

class BidDataAccessObject
{
public:
    BidDataAccessObject(){};
    ~BidDataAccessObject(){};

    ECommandResult InsertBid(const Bid& user);
};

#endif // BidDAO_H
