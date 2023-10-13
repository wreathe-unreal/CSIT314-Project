#include "CafeManagerWindow.h"
#include "ui_CafeManagerWindow.h"

CafeManagerWindow::CafeManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CafeManagerWindow)
{
    ui->setupUi(this);
}

CafeManagerWindow::~CafeManagerWindow()
{
    delete ui;
}
