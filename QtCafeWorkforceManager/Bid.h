#pragma once
#include "Shift.h"
#include "UserTypes.h"

enum EBidStatus
{
    PENDING,
    APPROVED,
    REJECTED
};

class Bid
{
    public:
        CafeStaff* StaffMember;
        Shift* ShiftRequested;
        EStaffRoles Role; //cannot bid for role which is already filled for a shift
        void SetStatus();
    
};
