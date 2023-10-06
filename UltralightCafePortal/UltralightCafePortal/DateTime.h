#pragma once
#include <iostream>
#include <sstream>
#include <string>

class Bid;
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
    }
    
    private:
        void Parse(string& DateString); //DD-MM-YYYY formatted string
        bool ValidateHour(Bid& bid);
};
