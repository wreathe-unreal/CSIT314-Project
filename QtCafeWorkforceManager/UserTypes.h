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
        EStaffRole Role;
        string Username;
        User(int userID, string username, string hashedPassword)
        {
            Role = EStaffRole::ESR_NonStaff;
            UserID = userID;
            Username = username;
            HashedPassword = hashedPassword;
        }
        string HashedPassword;
        int UserID;
        virtual ~User() {} // virtual destructor
    
};

class SysAdmin : public User
{
    public:
        SysAdmin(int userID, string username, string hashedPassword)
            : User(userID, username, hashedPassword) // This calls the base class constructor
        {
        }
    private:
        void CreateUser();
        void DeleteUser();
    
};

class CafeOwner : public User
{
    public:
        CafeOwner(int userID, string username, string hashedPassword)
            : User(userID, username, hashedPassword) // This calls the base class constructor
        {
        }
    private:
        void ViewShifts();
        void ManageShifts();
    
};

class CafeManager : public User
{
    public:
        CafeManager(int userID, string username, string hashedPassword)
            : User(userID, username, hashedPassword) // This calls the base class constructor
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

        vector<Shift> Shifts;

        CafeStaff(int userID, string username, string hashedPassword, vector<Shift> shifts)
            : User(userID, username, hashedPassword) // This calls the base class constructor
        {
            Shifts = shifts;
        }
    private:
        void BidForShift(Shift shift);
        void ViewShiftStatus(Shift shift);        
};

#endif
