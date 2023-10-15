#ifndef SHIFTDAO_H
#define SHIFTDAO_H
#include "Enums.h"
#include "NewShift.h"
#include "Shift.h"
#include "User.h"

#define DATABASE QApplicationGlobal::CafeDB

class ShiftDataAccessObject
{
public:
    ShiftDataAccessObject(){};
    ~ShiftDataAccessObject(){};

    //uncoded
    QVector<Shift> GetAllShifts();
    ECommandResult InsertShift(NewShift newShift);
    ECommandResult AssignStaff(Shift shift, User user);
    Shift GetShift(Shift shift);
    std::vector<User> GetStaff(Shift shift);
    std::vector<User> GetUnassignedStaff(Shift shift);
    std::vector<User> GetBidders(Shift shift);
    std::vector<Shift> GetByDate(QDate date);
    std::vector<Shift> GetByUser(std::string username);

    //coded

};

#endif // SHIFTDAO_H
