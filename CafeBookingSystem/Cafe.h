#pragma once
#include <string>
#include <vector>

class Shift;

class Cafe
{
public:
    std::string Name;
    std::vector<Shift> Shifts;

    void AddShift(Shift shift);
    void RemoveShift(Shift shift);
    
};
