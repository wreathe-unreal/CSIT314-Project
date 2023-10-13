#include "CafeOwnerWindow.h"
#include "ui_CafeOwnerWindow.h"

CafeOwnerWindow::CafeOwnerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CafeOwnerWindow)
{
    ui->setupUi(this);
}

CafeOwnerWindow::~CafeOwnerWindow()
{
    delete ui;
}
