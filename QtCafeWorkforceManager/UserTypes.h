#pragma once
#ifndef USERTYPES_H
#define USERTYPES_H
#include <string>
#include <vector>

class Shift;
class Bid;
class CafeStaff;

using namespace std;

enum class EUserTypes
{
    EUT_SysAdmin, //0
    EUT_CafeOwner, //1
    EUT_CafeMAnager, //2
    EUT_CafeStaff //3
};

enum class EStaffRoles
{
    ESR_Chef, //1
    ESR_Cashier, //2
    ESR_Waiter //3
};

class User
{
    public:
        string Username;
    private:
        string EncryptedPassword;
    
};

class SysAdmin : public User
{
    private:
        void CreateUser();
        void DeleteUser();
    
};

class CafeOwner : public User
{
private:
    void ViewShifts();
    void ManageShifts();
    
};

class CafeManager : public User
{
    private:
        vector<Bid> ReviewBids();
        void ApproveBid(Bid bid);
        void RejectBid(Bid bid);
        vector<CafeStaff> ListCafeStaff();
        void AssignShift(CafeStaff staff, Shift shift);
};


class CafeStaff : public User
{
    public:
        EStaffRoles Role;
        vector<Shift> Shifts;
    private:
        int MaxShifts;
        void BidForShift(Shift shift);
        void ViewShiftStatus(Shift shift);        
};

#endif
