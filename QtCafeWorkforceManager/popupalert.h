#ifndef POPUPALERT_H
#define POPUPALERT_H

#include <QDialog>

namespace Ui {
class PopupAlert;
}

class PopupAlert : public QDialog
{
    Q_OBJECT

public:
    explicit PopupAlert(QWidget *parent = nullptr);
    ~PopupAlert();
    void bidConfirm();
    void bidConflict();
    void bidDelete();
    void bidDelFail();
    void bidError();

private:
    Ui::PopupAlert *ui;
};

#endif // POPUPALERT_H
