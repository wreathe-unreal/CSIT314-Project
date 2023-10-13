#ifndef SYSADMINWINDOW_H
#define SYSADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SysAdminWindow;
}

class SysAdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SysAdminWindow(QWidget *parent = nullptr);
    ~SysAdminWindow();

private:
    Ui::SysAdminWindow *ui;
};

#endif // SYSADMINWINDOW_H
