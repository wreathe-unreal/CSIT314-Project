#ifndef ENUMS_H
#define ENUMS_H
#include <stdexcept>

enum class ECommandResult
{
    ECR_SUCCESS,
    ECR_FAILURE
};

enum class EShiftStatus
{
    EBS_PENDING,
    EBS_APPROVED,
    EBS_REJECTED
};

enum class EUserProfile
{
    EUP_SysAdmin, //0
    EUP_CafeOwner, //1
    EUP_CafeManager, //2
    EUP_CafeStaff //3
};

enum class EStaffRole
{
    ESR_NonStaff, //0
    ESR_Chef, //1
    ESR_Cashier, //2
    ESR_Waiter //3
};

EUserProfile IntToEUserType(int input);

int EUserTypeToInt(EUserProfile UserType);

int EStaffRoleToInt(EStaffRole UserRole);

EStaffRole IntToEStaffRole(int input);

EShiftStatus IntToEShiftStatus(int input);

int EShiftStatusToInt(EShiftStatus ShiftStatus);
#endif // ENUMS_H
