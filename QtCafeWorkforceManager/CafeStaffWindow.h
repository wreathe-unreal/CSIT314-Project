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

private:
    Ui::CafeStaffWindow *ui;
    void OnLogoutTriggered();
};

#endif // CAFESTAFFWINDOW_H
