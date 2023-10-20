#include "Enums.h"
QString EUserProfileToQString(EUserProfile eup)
{
    switch(eup)
    {
    case EUserProfile::EUP_CafeManager: return "Cafe Manager";
    case EUserProfile::EUP_SysAdmin: return "Sys Admin";
    case EUserProfile::EUP_CafeStaff: return "Cafe Staff";
    case EUserProfile::EUP_CafeOwner: return "Cafe Owner";
    default: return "Unknown";
    }
}

QString EBidStatusToQString(EBidStatus ebs)
{
    switch(ebs)
    {
    case EBidStatus::EBS_APPROVED: return "Approved";
    case EBidStatus::EBS_PENDING: return "Pending";
    case EBidStatus::EBS_REJECTED: return "Rejected";
    default: return "Unknown";
    }
}

QString EStaffRoleToQString(EStaffRole esr)
{
    switch(esr)
    {
    case EStaffRole::ESR_Cashier: return "Cashier";
    case EStaffRole::ESR_Chef: return "Chef";
    case EStaffRole::ESR_Waiter: return "Waiter";
    case EStaffRole::ESR_NonStaff: return "Non-Staff";
    default: return "Unknown";
    }
}

QString EDatabaseResultToQString(EDatabaseResult edr)
{
    switch(edr)
    {
    case EDatabaseResult::EDR_FAILURE: return "Failure";
    case EDatabaseResult::EDR_SUCCESS: return "Success";
    case EDatabaseResult::EDR_UNINITIALIZED: return "Uninitialized";
    default: return "Unknown";
    }
}

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

EBidStatus IntToEShiftStatus(int input)
{
    switch(input)
    {
        case 0: return EBidStatus::EBS_PENDING;
        case 1: return EBidStatus::EBS_APPROVED;
        case 2: return EBidStatus::EBS_REJECTED;
        default: throw std::invalid_argument("Invalid shift status");
    }
}

int EShiftStatusToInt(EBidStatus ShiftStatus)
{
    switch(ShiftStatus)
    {
        case EBidStatus::EBS_PENDING: return 0;
        case EBidStatus::EBS_APPROVED: return 1;
        case EBidStatus::EBS_REJECTED: return 2;
        default: throw std::invalid_argument("Invalid user type");
    }
}

EStaffRole QStringToEStaffRole(QString esr)
{
    if(esr == "Non-Staff")
    {
        return EStaffRole::ESR_NonStaff;
    }
    if(esr == "Chef")
    {
        return EStaffRole::ESR_Chef;
    }
    if(esr == "Cashier")
    {
        return EStaffRole::ESR_Cashier;
    }
    if(esr =="Waiter")
    {
        return EStaffRole::ESR_Waiter;
    }

    return EStaffRole::ESR_NonStaff;
}

EUserProfile QStringToEUserProfile(QString eup)
{
    if(eup == "Sys Admin")
    {
        return EUserProfile::EUP_SysAdmin;
    }
    if(eup == "Cafe Manager")
    {
        return EUserProfile::EUP_CafeManager;
    }
    if(eup == "Cafe Staff")
    {
        return EUserProfile::EUP_CafeStaff;
    }
    if(eup == "Cafe Owner")
    {
        return EUserProfile::EUP_CafeOwner;
    }

    return EUserProfile::EUP_CafeStaff;
}

EBidStatus QStringToEBidStatus(QString ebs)
{
    if(ebs == "Rejected")
    {
        return EBidStatus::EBS_REJECTED;
    }

    if(ebs == "Approved")
    {
        return EBidStatus::EBS_APPROVED;
    }

    if(ebs == "Pending")
    {
        return EBidStatus::EBS_PENDING;
    }
}
