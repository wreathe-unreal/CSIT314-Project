#include "PopUp.h"
#include "QApplicationGlobal.h"
#include "ui_PopUp.h"

#include <QStyle>

PopUp::PopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUp)
{
    ui->setupUi(this);
    QStyle *style = QApplicationGlobal::style();
    WarningIcon = style->standardIcon(QStyle::SP_MessageBoxWarning); // For warning icon
    CriticalIcon = style->standardIcon(QStyle::SP_MessageBoxCritical);
    InformationIcon = style->standardIcon(QStyle::SP_MessageBoxInformation);
    QuestionIcon = style->standardIcon(QStyle::SP_MessageBoxQuestion);
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::Success()
{
    this->setWindowTitle("Success!");
    ui->popupIcon->setPixmap(InformationIcon.pixmap(QSize(61,61)));
    ui->popupIcon->show();
}

void PopUp::Error()
{
    this->setWindowTitle("Error!");
    ui->popupIcon->setPixmap(CriticalIcon.pixmap(QSize(61,61)));
    ui->popupIcon->show();
}

//
// ADMIN ALERTS
//

void PopUp::AdminNoUserError()
{
    this->Error();
    ui->popupText->setText("No user selected!");
    this->exec();
}

void PopUp::AdminUserUpdated()
{
    this->Success();
    ui->popupText->setText("User is successfully updated.");
    this->exec();
}

void PopUp::AdminUserUpdateError()
{
    this->Error();
    ui->popupText->setText("User is not updated.");
    this->exec();
}

void PopUp::AdminUserCreated()
{
    this->Success();
    ui->popupText->setText("User is successfully created.");
    this->exec();
}

void PopUp::AdminUserCreateError()
{
    this->Error();
    ui->popupText->setText("User is not created.");
    this->exec();
}

void PopUp::AdminUserDeleted()
{
    this->Success();
    ui->popupText->setText("User is successfully deleted.");
    this->exec();
}

void PopUp::AdminUserDeleteError()
{
    this->Error();
    ui->popupText->setText("User is not deleted.");
    this->exec();
}

void PopUp::AdminEUPSearchError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("No user with the specified User Profile found.");
    this->exec();
}

//
// ADMIN ALERTS END
//

//
// STAFF ALERTS
//

void PopUp::StaffSlotBuildError()
{
    this->Error();
    ui->popupText->setText("Could not build and display work slots.");
    this->exec();
}

void PopUp::StaffInfoUpdated()
{
    this->Success();
    ui->popupText->setText("Your information has been updated!");
    this->exec();
}

void PopUp::StaffInfoUpdateFail()
{
    this->Error();
    ui->popupText->setText("Your information was not updated.");
    this->exec();
}

void PopUp::StaffBidEmptyError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("Please select one slot to bid for.");
    this->exec();
}

void PopUp::StaffBidConflictError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("One of the selected bid(s) has already been bid for!");
    this->exec();
}

void PopUp::StaffBidSubmitted()
{
    this->Success();
    ui->popupText->setText("You have successfully submitted your bid(s).");
    this->exec();
}

void PopUp::StaffBidDeleted()
{
    this->Success();
    ui->popupText->setText("You have successfully deleted your bid(s).");
    this->exec();
}

void PopUp::StaffBidDeleteError()
{
    this->Error();
    ui->popupText->setText("One of the selected bid(s) could not be deleted.");
    this->exec();
}

void PopUp::StaffSlotSearchResult(QString str)
{
    this->Success();
    ui->popupText->setText("Slot search success! " + str + " results found.");
    this->exec();
}

void PopUp::StaffSearchEmptyError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("Search resulted in 0 work slots found.");
    this->exec();
}

void PopUp::StaffSearchError()
{
    this->Error();
    ui->popupText->setText("Error encountered while searching for work slots.");
    this->exec();
}

void PopUp::StaffUpdateBidSelectionError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("Only one bid can be updated to another single bid at a time!");
    this->exec();
}

void PopUp::StaffUpdateBidEmptyError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("No bid was selected to be updated for/with.");
    this->exec();
}

void PopUp::StaffDeleteDuringUpdateError()
{
    this->Error();
    ui->popupText->setText("Could not update bid while deleting an older bid.");
    this->exec();
}

void PopUp::StaffBidUpdated()
{
    this->Success();
    ui->popupText->setText("Your bid has been successfully updated.");
    this->exec();
}

//
// STAFF ALERTS END
//


//
// OWNER ALERTS
//
void PopUp::OwnerSlotSearchResult(int nResults)
{
    this->Success();
    ui->popupText->setText("Slot search successful: " + QString::number(nResults) + " results found.");

}
void PopUp::OwnerSlotCreated()
{
    this->Success();
    ui->popupText->setText("Work slot has been successfully created.");
    this->exec();
}

void PopUp::OwnerSlotCreateError()
{
    this->Error();
    ui->popupText->setText("Work slot could not be created.");
    this->exec();
}

void PopUp::OwnerSlotNullError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("No work slot was selected.");
    this->exec();
}

void PopUp::OwnerSlotDeleted()
{
    this->Success();
    ui->popupText->setText("Work slot has been successfully deleted.");
    this->exec();
}

void PopUp::OwnerSlotDeleteError()
{
    this->Error();
    ui->popupText->setText("Work slot could not be deleted.");
    this->exec();
}

void PopUp::OwnerSlotDurationError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("Work slot has no valid duration!");
    this->exec();
}

void PopUp::OwnerSlotUpdated()
{
    this->Success();
    ui->popupText->setText("Work slot has been successfully updated.");
    this->exec();
}

void PopUp::OwnerSlotUpdateError()
{
    this->Error();
    ui->popupText->setText("Work slot could not be updated.");
    this->exec();
}

//
// OWNER ALERTS END
//

//
// MANAGER ALERTS
//

void PopUp::ManagerNullSelectionError()
{
    this->Error();
    ui->popupText->setText("No staff member was selected!");
    this->exec();
}

void PopUp::ManagerApprovalError()
{
    this->Error();
    ui->popupText->setText("Database error when approving staff member!");
    this->exec();
}

void PopUp::ManagerMaxSlotsError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("User is already working at their maximum requested capacity!");
    this->exec();
}

void PopUp::ManagerUnapprovalError()
{
    this->Error();
    ui->popupText->setText("Database error when unapproving staff member!");
    this->exec();
}

void PopUp::ManagerUnapprovalWarning()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("Unapproval successful, however if this staff member was idle when approved, please reject their bid as it was created during approval.");
}
void PopUp::ManagerRejectError()
{
    this->Error();
    ui->popupText->setText("Database error when rejecting staff member!");
    this->exec();
}

void PopUp::ManagerSearchEmptyError()
{
    this->Error();
    ui->popupIcon->setPixmap(WarningIcon.pixmap(QSize(61,61)));
    ui->popupText->setText("Worklot search found no results.");
    this->exec();
}

void PopUp::ManagerSearchError()
{
    this->Error();
    ui->popupText->setText("Slot search encountered an error.");
    this->exec();
}


//
// MANAGER ALERTS END
//
