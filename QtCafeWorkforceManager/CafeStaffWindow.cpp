#include "CafeStaffWindow.h"
#include "ui_CafeStaffWindow.h"

CafeStaffWindow::CafeStaffWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CafeStaffWindow)
{
    ui->setupUi(this);
}

CafeStaffWindow::~CafeStaffWindow()
{
    delete ui;
}
