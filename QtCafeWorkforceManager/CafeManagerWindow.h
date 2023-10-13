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

private:
    Ui::CafeManagerWindow *ui;
};

#endif // CAFEMANAGERWINDOW_H
