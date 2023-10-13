#include "Enums.h"

EUserProfile IntToEUserProfile(int input)
{
    switch(input)
    {
    case 0: return EUserProfile::EUP_SysAdmin;
    case 1: return EUserProfile::EUP_CafeOwner;
    case 2: return EUserProfile::EUP_CafeManager;
    case 3: return EUserProfile::EUP_CafeStaff;
    default: throw std::invalid_argument("Invalid user type");
    }
}

int EUserProfileToInt(EUserProfile UserType)
{
    switch(UserType)
    {
    case EUserProfile::EUP_SysAdmin: return 0;
    case EUserProfile::EUP_CafeOwner: return 1;
    case EUserProfile::EUP_CafeManager: return 2;
    case EUserProfile::EUP_CafeStaff: return 3;
    default: throw std::invalid_argument("Invalid user type");
    }
}

int EStaffRoleToInt(EStaffRole UserRole)
{
    switch(UserRole)
    {
    case EStaffRole::ESR_NonStaff: return 0;
    case EStaffRole::ESR_Chef: return 1;
    case EStaffRole::ESR_Cashier: return 2;
    case EStaffRole::ESR_Waiter: return 3;
    default: throw std::invalid_argument("Invalid user type");
    }
}

EStaffRole IntToEStaffRole(int input)
{
    switch(input)
    {
    case 0: return EStaffRole::ESR_NonStaff;
    case 1: return EStaffRole::ESR_Chef;
    case 2: return EStaffRole::ESR_Cashier;
    case 3: return EStaffRole::ESR_Waiter;
    default: throw std::invalid_argument("Invalid staff role");
    }
}

EShiftStatus IntToEShiftStatus(int input)
{
    switch(input)
    {
    case 0: return EShiftStatus::EBS_PENDING;
    case 1: return EShiftStatus::EBS_APPROVED;
    case 2: return EShiftStatus::EBS_REJECTED;
    default: throw std::invalid_argument("Invalid shift status");
    }
}

int EShiftStatusToInt(EShiftStatus ShiftStatus)
{
    switch(ShiftStatus)
    {
    case EShiftStatus::EBS_PENDING: return 0;
    case EShiftStatus::EBS_APPROVED: return 1;
    case EShiftStatus::EBS_REJECTED: return 2;
    default: throw std::invalid_argument("Invalid user type");
    }
}
