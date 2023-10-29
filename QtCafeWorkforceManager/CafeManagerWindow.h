#ifndef CAFEMANAGERWINDOW_H
#define CAFEMANAGERWINDOW_H

#include <QMainWindow>

namespace Ui {
class CafeManagerWindow;
}

class CafeManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CafeManagerWindow(QWidget *parent = nullptr);
    ~CafeManagerWindow();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_slotTable_itemSelectionChanged();

    void on_unapproveButton_clicked();

    void on_approveButton_clicked();

private:
    Ui::CafeManagerWindow *ui;
    void OnLogoutTriggered();
};

#endif // CAFEMANAGERWINDOW_H
