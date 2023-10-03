#pragma once
#include <vector>
#include <map>

#include "Time.h"
using namespace std;

enum EStaffRoles : int;

class Shift
{
public:
    Time ShiftDateTime
    map<EStaffRoles, int> RequiredStaffMap;
    map<EStaffRoles, vector<CafeStaff>> AssignedStaffMap;

private:
    bool bIsFullAllocated;

public:
    bool IsFullyAllocated(){ return bIsFullAllocated;}
    
};
