#ifndef QAPPLICATIONGLOBAL_H
#define QAPPLICATIONGLOBAL_H
#include <QApplication>
#include "Controller.h"
#include "ShiftDAO.h"
#include "UserDAO.h"
#include <QSqlDatabase>


class QApplicationGlobal : public QApplication
{
    Q_OBJECT

    public:
        QApplicationGlobal(int &argc, char **argv);
        ~QApplicationGlobal();

        static std::string CurrentUsername;
        static QSqlDatabase CafeDB;
        static Controller* ControllerPtr;
        static UserDataAccessObject UserDAO;
        static ShiftDataAccessObject ShiftDAO;

        static Controller* GetController();
        static void SafeDeleteController();
};

#endif // QAPPLICATIONGLOBAL_H

