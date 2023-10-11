#ifndef ENUMS_H
#define ENUMS_H
#include <stdexcept>

enum class EShiftStatus
{
    EBS_PENDING,
    EBS_APPROVED,
    EBS_REJECTED
};

enum class EUserType
{
    EUT_SysAdmin, //0
    EUT_CafeOwner, //1
    EUT_CafeManager, //2
    EUT_CafeStaff //3
};

enum class EStaffRole
{
    ESR_NonStaff, //0
    ESR_Chef, //1
    ESR_Cashier, //2
    ESR_Waiter //3
};

EUserType IntToEUserType(int input);

int EUserTypeToInt(EUserType UserType);

int EStaffRoleToInt(EStaffRole UserRole);

EStaffRole IntToEStaffRole(int input);

EShiftStatus IntToEShiftStatus(int input);

int EShiftStatusToInt(EShiftStatus ShiftStatus);
#endif // ENUMS_H
