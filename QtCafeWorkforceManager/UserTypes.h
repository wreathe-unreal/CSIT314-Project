#pragma once
#ifndef USERTYPES_H
#define USERTYPES_H
#include <string>
#include <vector>
#include "Enums.h"
#include "Shift.h"

class Bid;
class CafeStaff;

using namespace std;

class User
{
    public:
        int UserID;
        User()
        {
        }
        virtual ~User() {} // virtual destructor
    
};

class SysAdmin : public User
{
    public:
        SysAdmin(): User() // This calls the base class constructor
        {
        }
    private:
        void CreateUser();
        void DeleteUser();
    
};

class CafeOwner : public User
{
    public:
        CafeOwner(): User() // This calls the base class constructor
        {
        }
    private:
        void ViewShifts();
        void ManageShifts();
    
};

class CafeManager : public User
{
    public:
        CafeManager(): User() // This calls the base class constructor
        {
        }
    private:
        void ReviewBids();
        void ApproveBid(Bid bid);
        void RejectBid(Bid bid);
        void AssignShift(CafeStaff staff, Shift shift);
};


class CafeStaff : public User
{
    public:
        CafeStaff() : User() // This calls the base class constructor
        {
        }
    private:
        void BidForShift(Shift shift);
        void ViewShiftStatus(Shift shift);        
};

#endif
