#ifndef CAFEMANAGERWINDOW_H
#define CAFEMANAGERWINDOW_H

#include "Bid.h"

#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class CafeManagerWindow;
}

class CafeManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CafeManagerWindow(QWidget *parent = nullptr);
    ~CafeManagerWindow();

    void Reject(QTableWidget *tableWidget, Ui::CafeManagerWindow *ui);
    void Approve(QTableWidget *tableWidget, Ui::CafeManagerWindow *ui);
    void Assign(QTableWidget *tableWidget, Ui::CafeManagerWindow *ui, Bid newBid);
private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_slotTable_itemSelectionChanged();

    void on_unapproveButton_clicked();

    void on_approveButton_clicked();

    void on_showWorkslotsButton_clicked();

    void on_rejectButton_clicked();

    void on_chefRejectButton_clicked();

    void on_cashierRejectButton_clicked();

    void on_waiterRejectButton_clicked();

    void on_rejectedUnreject_clicked();

    void on_chefApproveButton_clicked();

    void on_cashierApproveButton_clicked();

    void on_waiterApproveButton_clicked();

    void on_rejectedApprove_clicked();

    void on_assignButton_clicked();

private:
    Ui::CafeManagerWindow *ui;
    void OnLogoutTriggered();
};

#endif // CAFEMANAGERWINDOW_H
