#pragma once
#include "Shift.h"

enum EBidStatus
{
    PENDING,
    APPROVED,
    REJECTED
};

class Bid
{
    public:
        Cafe* CafeLocation;
        CafeStaff* StaffMember;
        Shift* ShiftRequested;
        EStaffRoles Role; //cannot bid for role which is already filled for a shift
        void SetStatus();
    
};
