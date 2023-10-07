#pragma once
#include <string>
#include <vector>

class Shift;

class Cafe
{
    public:
        unsigned int OpenHour; //24h format
        unsigned int CloseHour; //24h format
        std::string Name;
        std::vector<Shift> Shifts;

        void AddShift(Shift shift);
        void RemoveShift(Shift shift);
    
};
