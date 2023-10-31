#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QIcon>

namespace Ui {
class PopUp;
}

class PopUp : public QDialog
{
    Q_OBJECT

public:
    QIcon WarningIcon;
    QIcon CriticalIcon;
    QIcon QuestionIcon;
    QIcon InformationIcon;

    explicit PopUp(QWidget *parent = nullptr);
    ~PopUp();
    void Success();
    void Error();
    void AdminNoUserError();
    void AdminUserUpdated();
    void AdminUserUpdateError();
    void AdminUserCreated();
    void AdminUserCreateError();
    void AdminUserDeleted();
    void AdminUserDeleteError();
    void AdminEUPSearchError();
    void StaffSlotBuildError();
    void StaffInfoUpdated();
    void StaffInfoUpdateFail();
    void StaffBidEmptyError();
    void StaffBidConflictError();
    void StaffBidSubmitted();
    void StaffBidDeleted();
    void StaffBidDeleteError();
    void StaffSlotSearchResult(QString);
    void StaffSearchEmptyError();
    void StaffSearchError();
    void StaffUpdateBidSelectionError();
    void StaffUpdateBidEmptyError();
    void StaffDeleteDuringUpdateError();
    void StaffBidUpdated();
    void OwnerSlotCreated();
    void OwnerSlotCreateError();
    void OwnerSlotNullError();
    void OwnerSlotDeleted();
    void OwnerSlotDeleteError();
    void OwnerSlotDurationError();
    void OwnerSlotUpdated();
    void OwnerSlotUpdateError();

    void ManagerNullSelectionError();
    void ManagerApprovalError();
    void ManagerUnapprovalError();
    void ManagerMaxSlotsError();
    void ManagerRejectError();
    void OwnerSlotSearchResult(int nResults);
    void ManagerSearchEmptyError();
    void ManagerSearchError();
private:
    Ui::PopUp *ui;
};

#endif // POPUP_H
