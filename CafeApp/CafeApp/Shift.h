#pragma once
#include <vector>
#include <map>
#include "Cafe.h"
#include "DateTime.h"
class CafeStaff;

using namespace std;

enum EStaffRoles : int;

class Shift
{
public:
    Cafe* CafeLocation;
    DateTime Time;
    map<EStaffRoles, int> RequiredStaffMap;
    map<EStaffRoles, vector<CafeStaff>> AssignedStaffMap;

private:
    bool bIsFullAllocated;

public:
    bool IsFullyAllocated(){ return bIsFullAllocated;}
    
};
