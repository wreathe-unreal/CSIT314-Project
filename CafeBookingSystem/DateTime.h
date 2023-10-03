#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class DateTime
{
    public:
    unsigned int Year;
    unsigned int Month;
    unsigned int Day;
    unsigned int Hour;
    

    DateTime(string DateString)
    {
        Parse(DateString);
        ValidateHour();
    }
    
    private:
        void Parse(string& DateString); //DD-MM-YYYY formatted string
        void ValidateHour();
};
