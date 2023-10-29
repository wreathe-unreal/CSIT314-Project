#ifndef WORKSLOTCREATOR_H
#define WORKSLOTCREATOR_H

#include <QDialog>
#include "QApplicationGlobal.h"
#include "popupalert.h"

namespace Ui {
class WorkSlotCreator;
}

class WorkSlotCreator : public QDialog
{
    Q_OBJECT

public:
    explicit WorkSlotCreator(QWidget *parent = nullptr);
    ~WorkSlotCreator();

private slots:
    void on_createButton_clicked();

private:
    Ui::WorkSlotCreator *ui;
};

#endif // WORKSLOTCREATOR_H
