#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) // Changed from AuthWindow to MainWindow
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
