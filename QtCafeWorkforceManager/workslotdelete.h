#ifndef WORKSLOTDELETE_H
#define WORKSLOTDELETE_H

#include <QDialog>

namespace Ui {
class WorkSlotDelete;
}

class WorkSlotDelete : public QDialog
{
    Q_OBJECT

public:
    explicit WorkSlotDelete(QWidget *parent = nullptr);
    ~WorkSlotDelete();

private slots:
    void on_workslottable_clicked(const QModelIndex &index);

    void on_deleteBid_clicked();

private:
    Ui::WorkSlotDelete *ui;
    std::vector<int> rows;
};

#endif // WORKSLOTDELETE_H
