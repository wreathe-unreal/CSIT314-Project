#include "PopUp.h"
#include "ui_PopUp.h"

PopUp::PopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUp)
{
    ui->setupUi(this);
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::Success()
{
    this->setWindowTitle("Success!");
    QIcon icon = QIcon::fromTheme("dialog-information");
    ui->popupIcon->setPixmap(icon.pixmap(QSize(61,61)));
    ui->popupIcon->repaint();
}

void PopUp::Error()
{
    this->setWindowTitle("Error!");
    QIcon icon = QIcon::fromTheme("dialog-critical");
    ui->popupIcon->setPixmap(icon.pixmap(QSize(61,61)));
    ui->popupIcon->repaint();
}

void PopUp::noUser()
{
    ui->popupText->setText("No user selected!");
}

void PopUp::userUpdate()
{
    ui->popupText->setText("User is successfully updated.");
}

void PopUp::userUpdateFail()
{
    ui->popupText->setText("User is not updated.");
}

void PopUp::userCreate()
{
    ui->popupText->setText("User is successfully created.");
}

void PopUp::userCreateFail()
{
    ui->popupText->setText("User is not created.");
}

void PopUp::userDelete()
{
    ui->popupText->setText("User is successfully deleted.");
}

void PopUp::userDeleteFail()
{
    ui->popupText->setText("User is not deleted.");
}

void PopUp::nullUser()
{
    ui->popupText->setText("No user with the specified User Profile found.");
}

void PopUp::slotError()
{
    ui->popupText->setText("Could not build and display work slots.");
}

void PopUp::infoUpdate()
{
    ui->popupText->setText("Your information has been updated!");
}

void PopUp::infoUpdateFail()
{
    ui->popupText->setText("Your information was not updated.");
}

void PopUp::bidEmpty()
{
    ui->popupText->setText("Please select one slot to bid for.");
}

void PopUp::bidConflict()
{
    ui->popupText->setText("One of the selected bid(s) has already been bid for!");
}

void PopUp::bidSuccess()
{
    ui->popupText->setText("You have successfully submitted your bid(s).");
}

void PopUp::bidDelete()
{
    ui->popupText->setText("You have successfully deleted your bid(s).");
}

void PopUp::bidDeleteFail()
{
    ui->popupText->setText("One of the selected bid(s) could not be deleted.");
}

void PopUp::searchSuccess(QString str)
{
    ui->popupText->setText("Slot search success! " + str + " results found.");
}

void PopUp::searchFail()
{
    ui->popupText->setText("Search resulted in 0 work slots found.");
}

void PopUp::searchError()
{
    ui->popupText->setText("Error encountered while searching for work slots.");
}

void PopUp::updateMulti()
{
    ui->popupText->setText("Only one bid can be updated to another single bid at a time!");
}

void PopUp::updateEmpty()
{
    ui->popupText->setText("No bid was selected to be updated for/with.");
}

void PopUp::updateFail()
{
    ui->popupText->setText("Could not update bid while deleting an older bid.");
}

void PopUp::updateSuccess()
{
    ui->popupText->setText("Your bid has been successfully updated.");
}

void PopUp::slotCreate()
{
    ui->popupText->setText("Work slot has been successfully created.");
}

void PopUp::slotCreateFail()
{
    ui->popupText->setText("Work slot could not be created.");
}

void PopUp::slotNull()
{
    ui->popupText->setText("No work slot was selected.");
}

void PopUp::slotDelete()
{
    ui->popupText->setText("Work slot has been successfully deleted.");
}

void PopUp::slotDeleteFail()
{
    ui->popupText->setText("Work slot could not be deleted.");
}

void PopUp::slotDurationNull()
{
    ui->popupText->setText("Work slot has no valid duration!");
}

void PopUp::slotUpdate()
{
    ui->popupText->setText("Work slot has been successfully updated.");
}

void PopUp::slotUpdateFail()
{
    ui->popupText->setText("Work slot could not be updated.");
}
