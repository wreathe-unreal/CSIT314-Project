#ifndef CAFEOWNERWINDOW_H
#define CAFEOWNERWINDOW_H

#include <QMainWindow>

namespace Ui {
class CafeOwnerWindow;
}

class CafeOwnerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CafeOwnerWindow(QWidget *parent = nullptr);
    ~CafeOwnerWindow();

private:
    Ui::CafeOwnerWindow *ui;
};

#endif // CAFEOWNERWINDOW_H
