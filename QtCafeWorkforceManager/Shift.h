#pragma once
#ifndef SHIFT_H
#define SHIFT_H
#include "Enums.h"
#include "Date.h"
#include <vector>
#include <string>
#include <map>
class CafeStaff;


using namespace std;

enum EStaffRoles : int;

class Shift
{
    public:
    bool bFull; //when all staff have been allocated this is true
    string Date;
    EShiftStatus Status;
    Shift(string date, EShiftStatus status)
    {
        Date = date;
        Status = status;
    }
    
    //required staff
    int NumChefs;
    int NumCashiers;
    int NumWaiters;
    
    //current staff
    int CurChefs;
    int CurCashiers;
    int CurWaiters;
    
};

#endif
