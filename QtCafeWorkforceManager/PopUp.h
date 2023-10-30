#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QIcon>

namespace Ui {
class PopUp;
}

class PopUp : public QDialog
{
    Q_OBJECT

public:
    explicit PopUp(QWidget *parent = nullptr);
    ~PopUp();
    void Success();
    void Error();
    void noUser();
    void userUpdate();
    void userUpdateFail();
    void userCreate();
    void userCreateFail();
    void userDelete();
    void userDeleteFail();
    void nullUser();
    void slotError();
    void infoUpdate();
    void infoUpdateFail();
    void bidEmpty();
    void bidConflict();
    void bidSuccess();
    void bidDelete();
    void bidDeleteFail();
    void searchSuccess(QString);
    void searchFail();
    void searchError();
    void updateMulti();
    void updateEmpty();
    void updateFail();
    void updateSuccess();
    void slotCreate();
    void slotCreateFail();
    void slotNull();
    void slotDelete();
    void slotDeleteFail();
    void slotDurationNull();
    void slotUpdate();
    void slotUpdateFail();

private:
    Ui::PopUp *ui;
};

#endif // POPUP_H
