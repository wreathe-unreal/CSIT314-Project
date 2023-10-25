#ifndef BIDDAO_H
#define BIDDAO_H
#include "Bid.h"
#include "Enums.h"

class BidDataAccessObject
{
    public:
        EDatabaseResult Result;
        void Insert(Bid newBid);
        QVector<Bid> GetBids();
        QVector<Bid> GetPending();
        QVector<Bid> GetApproved();
        QVector<Bid> GetRejected();
        QVector<Bid> SearchByUserID(int UserID);
        QVector<Bid> SearchBySlotID(int slotID);


};

#endif // BIDDAO_H
