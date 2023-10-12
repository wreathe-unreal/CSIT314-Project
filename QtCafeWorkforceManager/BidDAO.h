#ifndef BIDDAO_H
#define BIDDAO_H
#include "Enums.h"
#include "Bid.h"

class BidDAO
{
public:
    BidDAO(){};
    ~BidDAO(){};

    ECommandResult InsertBid(const Bid& user);
};

#endif // BidDAO_H
