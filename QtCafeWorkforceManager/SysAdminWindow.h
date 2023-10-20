#ifndef SYSADMINWINDOW_H
#define SYSADMINWINDOW_H

#include <QComboBox>
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

    void on_editButton_clicked();

    void on_createButton_clicked();

    void on_profileCombo_currentIndexChanged(int index);

    void on_profileComboCreate_currentIndexChanged(int index);

    void on_deleteButton_clicked();


    void on_searchButton_clicked();

private:
    Ui::SysAdminWindow *ui;
};

#endif // SYSADMINWINDOW_H
