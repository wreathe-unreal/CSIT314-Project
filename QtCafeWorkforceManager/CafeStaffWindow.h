#ifndef CAFESTAFFWINDOW_H
#define CAFESTAFFWINDOW_H

#include <QMainWindow>

namespace Ui {
class CafeStaffWindow;
}

class CafeStaffWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CafeStaffWindow(QWidget *parent = nullptr);
    ~CafeStaffWindow();

private slots:
    void on_editInfoButton_clicked();

    void on_bidButton_clicked();

    void on_availableTable_clicked(const QModelIndex &index);

    void on_pendingTable_clicked(const QModelIndex &index);

    void on_deleteButton_clicked();

    void on_workslotCalendar_clicked(const QDate &date);

    void on_pushButton_clicked();

private:
    Ui::CafeStaffWindow *ui;
    void OnLogoutTriggered();
};

#endif // CAFESTAFFWINDOW_H
