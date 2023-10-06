#include "Calendar.h"

#include <string>
#include <vector>
class Month;
class Day;
using namespace std;

int CurrentYear = 2023;

class Year
{
    vector<Month> Months;   
};

class Month
{
    vector<Day> Days;
    string Name;
};

class Day
{
    string Name;
};


//returns the name of the day (i.e. Sunday, Monday, etc) based on the DD/MM/YYYY info
//0 = sunday etc..
int GetDayNameIndex(int day, int month, int year)
{
 
    static int DayIndex[] = { 0, 3, 2, 5, 0, 3, 5, 1,
                       4, 6, 2, 4 };
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
    // January
    if (MonthNumber == 0)
        return (31);
 
    // February
    if (MonthNumber == 1)
    {
        // If the year is leap then February has
        // 29 days
        if (Year % 400 == 0 ||
                (Year % 4 == 0 && Year % 100 != 0))
            return (29);
        else
            return (28);
    }
 
    // March
    if (MonthNumber == 2)
        return (31);
 
    // April
    if (MonthNumber == 3)
        return (30);
 
    // May
    if (MonthNumber == 4)
        return (31);
 
    // June
    if (MonthNumber == 5)
        return (30);
 
    // July
    if (MonthNumber == 6)
        return (31);
 
    // August
    if (MonthNumber == 7)
        return (31);
 
    // September
    if (MonthNumber == 8)
        return (30);
 
    // October
    if (MonthNumber == 9)
        return (31);
 
    // November
    if (MonthNumber == 10)
        return (30);
 
    // December
    if (MonthNumber == 11)
        return (31);
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

void BuildCalendar(int Year)
{
    printf ("         Calendar - %d\n\n", Year);
    int days;
 
    // Index of the day from 0 to 6
    int current = GetDayNameIndex(1, 1, Year);
 
    // i --> Iterate through all the months
    // j --> Iterate through all the days of the
    //       month - i
    for (int i = 0; i < 12; i++)
    {
        days = NumberOfDays (i, Year);
 
        // Print the current month name
        printf("\n  ------------%s-------------\n",
               GetMonthName (i).c_str());
 
        // Print the columns
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
 
        // Print appropriate spaces
        int k;
        for (k = 0; k < current; k++)
            printf("     ");
 
        for (int j = 1; j <= days; j++)
        {
            printf("%5d", j);
 
            if (++k > 6)
            {
                k = 0;
                printf("\n");
            }
        }
 
        if (k)
            printf("\n");
 
        current = k;
    }
 
    return;
}
