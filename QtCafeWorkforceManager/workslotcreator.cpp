#include "workslotcreator.h"
#include "ui_workslotcreator.h"
#include "Controller.h"
#include "Slot.h"
#include "Response.h"

WorkSlotCreator::WorkSlotCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkSlotCreator)
{
    ui->setupUi(this);
}

WorkSlotCreator::~WorkSlotCreator()
{
    delete ui;
}

void WorkSlotCreator::on_createButton_clicked()
{

}

