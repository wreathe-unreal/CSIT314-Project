#ifndef SHIFTDAO_H
#define SHIFTDAO_H
#include "Enums.h"
#include "Shift.h"

class ShiftDAO
{
public:
    ShiftDAO(){};
    ~ShiftDAO(){};

    ECommandResult InsertShift(const Shift& user);
};

#endif // SHIFTDAO_H
