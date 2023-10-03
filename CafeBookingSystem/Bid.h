#pragma once
#include "Shift.h"
#include "UserTypes.h"

enum EBidStatus
{
    PENDING,
    
};

class Bid
{
    CafeStaff StaffMember;
    Shift ShiftRequested;
    EStaffRoles Role;
    void SetStatus();
    
};
