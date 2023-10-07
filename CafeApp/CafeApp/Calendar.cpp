#include "Calendar.h"
#include "Utils.h"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
class Month;
class Day;
using namespace std;

int GetCurrentYear()
{
    time_t currentTime = time(NULL);
    tm localTime;
    localtime_s(&localTime, &currentTime);
    
    // tm_year is the number of years since 1900
    return 1900 + localTime.tm_year;
}

//returns the name of the day (i.e. Sunday, Monday, etc) based on the DD/MM/YYYY info
//0 = sunday etc..
int GetDayNameIndex(int day, int month, int year)
{
 
    static int DayIndex[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    
    return ( year + year/4 - year/100 + year/400 + DayIndex[month-1] + day) % 7;
}
 
//returns the name of the month based on the #
string GetMonthName(int monthNumber)
{
    string MonthName[] = {"January", "February", "March",
                       "April", "May", "June",
                       "July", "August", "September",
                       "October", "November", "December"
                      };
 
    return (MonthName[monthNumber]);
}

//finds the number of days in a month
//Thirty days has September, April, June, and November.
//All the rest have thirty-one,
//Except for February alone, Which has twenty-eight days clear, And twenty-nine in each leap year."
int NumberOfDays(int MonthNumber, int Year)
{
    switch (MonthNumber)
    {
    case 0:  return 31;             // January
        case 1:                         // February
            if (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0))
                return 29;
            else
                return 28;
    case 2:  return 31;             // March
        case 3:  return 30;             // April
        case 4:  return 31;             // May
        case 5:  return 30;             // June
        case 6:  return 31;             // July
        case 7:  return 31;             // August
        case 8:  return 30;             // September
        case 9:  return 31;             // October
        case 10: return 30;             // November
        case 11: return 31;             // December
        default: return -1;             // Error value for unexpected MonthNumber
    }
}
 
// Function to print the calendar of the given year
// void PrintCalendar(int Year)
// {
//     printf ("         Calendar - %d\n\n", Year);
//     int days;
//  
//     // Index of the day from 0 to 6
//     int current = dayNumber (1, 1, Year);
//  
//     // i --> Iterate through all the months
//     // j --> Iterate through all the days of the
//     //       month - i
//     for (int i = 0; i < 12; i++)
//     {
//         days = numberOfDays (i, Year);
//  
//         // Print the current month name
//         printf("\n  ------------%s-------------\n",
//                getMonthName (i).c_str());
//  
//         // Print the columns
//         printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
//  
//         // Print appropriate spaces
//         int k;
//         for (k = 0; k < current; k++)
//             printf("     ");
//  
//         for (int j = 1; j <= days; j++)
//         {
//             printf("%5d", j);
//  
//             if (++k > 6)
//             {
//                 k = 0;
//                 printf("\n");
//             }
//         }
//  
//         if (k)
//             printf("\n");
//  
//         current = k;
//     }
//  
//     return;
// }

// void PrintMonth(Year year, int monthIndex)
// {
//     int FirstDayOffset = year.Months[monthIndex].FirstDayIndex;
//     
// }

void Calendar::DisplayCalendarMonth(HWND hWnd, HINSTANCE hInst, int MonthIndex)
{
    int xOffset = 10;
    int yOffset = 10;
    int xOffsetMonthStart = Months[MonthIndex].FirstDayIndex * 60;
        
    int dayCounter = 1;  // Initialize to 1 to represent the 1st day of the month
    int weekLength = 7;
    while(dayCounter <= Months[MonthIndex].TotalDays)
    {
        if(dayCounter == 1)
        {
            weekLength = 7 - Months[MonthIndex].FirstDayIndex; //handle first week offset
            
        }
        
        for(int j = 0; j < weekLength && dayCounter <= Months[MonthIndex].TotalDays; j++)
        {
            LPCWSTR ButtonTextPtr = StringToLPCWSTR(std::to_string(dayCounter));

            HWND hButton = CreateWindowW(
                L"BUTTON",  
                ButtonTextPtr,
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                xOffset + xOffsetMonthStart,
                yOffset,
                60,
                60,
                hWnd,
                NULL,
                hInst,
                NULL);

            xOffset += 60;
            delete[] ButtonTextPtr;
            dayCounter++;
        }
        weekLength = 7; //reset weekLength
        xOffsetMonthStart = 0;
        xOffset = 10;
        yOffset += 60;  // Increment yOffset for the next button (60 for button height + 10 for space)
    }
}

Calendar::Calendar(int YearNumberAnoDomini)
{
    YearNumberAD = YearNumberAnoDomini;

    // i --> Iterate through all the months
    for (int i = 0; i < 12; i++)
    {

        //1 to represent the first day of the month
        //fill calendar with month data
        Month NewMonth = Month(GetDayNameIndex(1, i+1, YearNumberAD), NumberOfDays(i, YearNumberAD), GetMonthName(i));
        Months.emplace_back(NewMonth);
    }
}