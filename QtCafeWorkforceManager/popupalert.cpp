#include "popupalert.h"
#include "ui_popupalert.h"

PopupAlert::PopupAlert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopupAlert)
{
    ui->setupUi(this);
}

PopupAlert::~PopupAlert()
{
    delete ui;
}

void PopupAlert::bidConfirm()
{
    ui->popupText->setText("You have successfully submitted your bid(s).");
}

void PopupAlert::bidConflict()
{
    ui->popupText->setText("There is already a bid for this work slot.");
}

void PopupAlert::bidDelete()
{
    ui->popupText->setText("You have successfully deleted selected bid(s).");
}

void PopupAlert::bidDelFail()
{
    ui->popupText->setText("Failed to delete bid for work slot.");
}

void PopupAlert::bidError()
{
    ui->popupText->setText("Failed to create slot in table.");
}
