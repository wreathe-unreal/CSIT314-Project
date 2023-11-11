#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QFocusEvent>

class QLE_Clearable : public QLineEdit {
    Q_OBJECT

public:
    explicit QLE_Clearable(QWidget *parent = nullptr) : QLineEdit(parent), cleared(false) {}

protected:
    void focusInEvent(QFocusEvent *e) override {
        QLineEdit::focusInEvent(e); // Call the base class implementation
        if (!cleared) { // Check if the line edit has been cleared before
            this->clear(); // Clear the text
            cleared = true; // Set the flag to true so it doesn't clear again
        }
    }

private:
    bool cleared; // A flag to keep track of the clearing state
};

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

        void on_QLE_Password_returnPressed();

    private:
        Ui::AuthWindow* ui;
};
#endif // AUTHWINDOW_H
