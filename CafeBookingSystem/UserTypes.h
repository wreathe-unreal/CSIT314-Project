#pragma once
#include <string>
#include <vector>

class Shift;
class Bid;
class CafeStaff;
class Cafe;
using namespace std;

enum EStaffRoles
{
    CHEF,
    CASHIER,
    WAITER
};

class User
{
    public:
        string Username;
        
        bool Authenticate(string Password);
        string EncryptPassword(string PlainTextPassword);
    private:
        string EncryptedPassword;
    
};

class SysAdmin : public User
{
    vector<Cafe*> Cafes;

    private:
        void CreateUser();
        void DeleteUser();
    
};

class CafeOwner : public User
{
public:
    vector<Cafe*> Cafes;
private:
    void ViewShifts();
    void ManageShifts();
    
};

class CafeManager : public User
{
    public:
        vector<Cafe*> Cafes;
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
        Cafe* Cafe;
        EStaffRoles Role;
        vector<Shift> Shifts;
    private:
        int MaxShifts;
        void BidForShift(Shift shift);
        void ViewShiftStatus(Shift shift);
    
        
};
