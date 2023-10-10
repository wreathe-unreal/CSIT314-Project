#pragma once
#ifndef SHIFT_H
#define SHIFT_H

#include "Date.h"
#include <vector>
#include <map>
class CafeStaff;


using namespace std;


enum EStaffRoles : int;

class Shift
{
public:
    Date DateShift;
    map<EStaffRoles, int> RequiredStaffMap;
    map<EStaffRoles, vector<CafeStaff>> AssignedStaffMap;

private:
    bool bIsFullAllocated;

public:
    bool IsFullyAllocated(){ return bIsFullAllocated;}
    
};

#endif
