#pragma once
#include <string>
#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <vector>

#include "framework.h"

class Month
{
public:
    int FirstDayIndex; //what day the first day of the month falls on
    int TotalDays; //total number of days;
    std::string Name;

    Month(int firstDayIndex, int totalDays, std::string Name)
    {
        this->FirstDayIndex = firstDayIndex;
        this->TotalDays = totalDays;
        this->Name = Name;
    }
};

class Calendar
{
    public:
    int YearNumberAD;
    std::vector<Month> Months;
    
    Calendar() = default;
    Calendar(int YearNumberAnoDomini);
    void DisplayCalendarMonth(HWND hWnd, HINSTANCE hInst, int MonthIndex);
};
