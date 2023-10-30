#ifndef BIDDAO_H
#define BIDDAO_H
#include "Bid.h"
#include "Enums.h"
#include "Response.h"
#include "User.h"

class BidDataAccessObject
{
    public:
        Response<Bid> GetBid(int bidID);
        Response<void> Insert(Bid newBid);
        Response<QVector<Bid>> GetBids();
        Response<QVector<Bid>> GetPending();
        Response<QVector<Bid>> GetApproved();
        Response<QVector<Bid>> GetRejected();
        Response<QVector<Bid>> SearchByUserID(int UserID);
        Response<QVector<Bid>> SearchBySlotID(int slotID);
        Response<void> Delete(int bidID);
        Response<User>  GetUserByBidID(int bidid);
        Response<void> ApproveBid(int bidid);
        Response<QVector<User>> GetStaff(int slotID);



};

#endif // BIDDAO_H
