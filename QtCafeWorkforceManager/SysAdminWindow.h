#ifndef SYSADMINWINDOW_H
#define SYSADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SysAdminWindow;
}

class SysAdminWindow : public QMainWindow
{
    Q_OBJECT
    QString UsernameBeforeEdit;

public:
    explicit SysAdminWindow(QWidget *parent = nullptr);
    ~SysAdminWindow();

private slots:
    void on_userTable_clicked(const QModelIndex &index);

private:
    Ui::SysAdminWindow *ui;
};

#endif // SYSADMINWINDOW_H
