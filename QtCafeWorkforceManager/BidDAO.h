#ifndef BIDDAO_H
#define BIDDAO_H
#include "Bid.h"
#include "Enums.h"
#include "QApplicationGlobal.h"

class BidDataAccessObject
{
    public:
        EDatabaseResult Result;
        QVector<Bid> GetBids();
        QVector<Bid> SearchByUsername(QString username);
        QVector<Bid> SearchBySlotID(int slotID);


};
#endif // BIDDAO_H
