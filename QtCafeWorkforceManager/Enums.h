#pragma once

#ifndef ENUMS_H
#define ENUMS_H
#include <QString>
#include <stdexcept>

enum class EDatabaseResult
{
    EDR_UNINITIALIZED,
    EDR_SUCCESS,
    EDR_FAILURE
};

enum class EBidStatus
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



QString EDatabaseResultToQString(EDatabaseResult edr);

QString EStaffRoleToQString(EStaffRole esr);

QString EBidStatusToQString(EBidStatus ebs);

QString EUserProfileToQString(EUserProfile eup);

EUserProfile IntToEUserProfile(int input);

int EUserProfileToInt(EUserProfile UserType);

int EStaffRoleToInt(EStaffRole UserRole);

EStaffRole IntToEStaffRole(int input);

EBidStatus IntToEShiftStatus(int input);

int EShiftStatusToInt(EBidStatus ShiftStatus);
#endif // ENUMS_H
