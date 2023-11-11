#ifndef BID_H
#define BID_H

#include <QDebug>
#include "Entity.h"
#include "Response.h"
#include "User.h"

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


        static Response<Bid> GetBid(int bidID);
        static Response<void> Insert(Bid newBid);
        static Response<QVector<Bid>> GetBids();
        static Response<QVector<Bid>> GetPending();
        static Response<QVector<Bid>> GetApproved();
        static Response<QVector<Bid>> GetRejected(int UserID);
        static Response<QVector<Bid>> SearchByUserID(int UserID);
        static Response<QVector<Bid>> SearchBySlotID(int slotID);
        static Response<void> Delete(int bidID);
        static Response<User>  GetUserByBidID(int bidid);
        static Response<void> ApproveBid(int bidid);
        static Response<QVector<int>> GetStaff(int slotID);
        static Response<QVector<User>> GetBidder(int slotID);
        static Response<void> RejectBid(int bidid);
        static Response<void> UnapproveBid(int bidid);
        static Response<QVector<int> > GetSlotIDsByUserID(int userID);
        static Response<QVector<int>> GetBiddersBySlotID(int slotID);
};

#endif // BID_H
