#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AuthWindow; }
QT_END_NAMESPACE

class AuthWindow : public QMainWindow
{
        Q_OBJECT

    public:
        AuthWindow(QWidget *parent =     nullptr);
        ~AuthWindow();

    private slots:
        void on_LoginButton_clicked();

        void on_QLE_Username_textChanged(const QString &arg1);

        void on_QLE_Password_textEdited(const QString &arg1);

    private:
        Ui::AuthWindow* ui;
};
#endif // AUTHWINDOW_H
