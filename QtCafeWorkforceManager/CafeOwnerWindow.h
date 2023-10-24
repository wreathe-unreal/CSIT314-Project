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

    private slots:

        void on_createButton_clicked();

        void on_deleteButton_clicked();

        void on_slotTable_clicked(const QModelIndex &index);

        void on_editButton_clicked();

        void on_searchButton_clicked();

        void on_showAllButton_clicked();

    private:
        Ui::CafeOwnerWindow *ui;

        void OnLogoutTriggered();
};

#endif // CAFEOWNERWINDOW_H
