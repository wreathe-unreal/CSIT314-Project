#include "SysAdminWindow.h"
#include "ui_SysAdminWindow.h"

SysAdminWindow::SysAdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SysAdminWindow)
{
    ui->setupUi(this);
}

SysAdminWindow::~SysAdminWindow()
{
    delete ui;
}
