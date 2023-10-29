#ifndef WORKSLOTBID_H
#define WORKSLOTBID_H

#include <QDialog>

namespace Ui {
class WorkSlotBid;
}

class WorkSlotBid : public QDialog
{
    Q_OBJECT

public:
    explicit WorkSlotBid(QWidget *parent = nullptr);
    ~WorkSlotBid();

private slots:
    void on_createBid_clicked();

    void on_workslottable_clicked(const QModelIndex &index);

private:
    Ui::WorkSlotBid *ui;
    std::vector<int> rows;
};

#endif // WORKSLOTBID_H
