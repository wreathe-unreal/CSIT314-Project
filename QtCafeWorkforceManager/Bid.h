#pragma once
#ifndef BID_H
#define BID_H


#include "Shift.h"
#include "UserTypes.h"

class Bid
{
    public:
        CafeStaff* StaffMember;
        Shift* ShiftRequested;
        EStaffRoles Role; //cannot bid for role which is already filled for a shift
        void SetStatus();
    
};

#endif
