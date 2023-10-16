#ifndef QAPPLICATIONGLOBAL_H
#define QAPPLICATIONGLOBAL_H
#include <QApplication>
#include "Controller.h"
#include "SlotDAO.h"
#include "UserDAO.h"
#include <QSqlDatabase>

#define DATABASE QApplicationGlobal::CafeDB

class QApplicationGlobal : public QApplication
{
    Q_OBJECT

    public:
        QApplicationGlobal(int &argc, char **argv);

        ~QApplicationGlobal()
        {
            this->SafeDeleteController();
            this->CafeDB.close();
        };

        static std::string CurrentUsername;
        static QSqlDatabase CafeDB;
        static Controller* ControllerPtr;
        static UserDataAccessObject UserDAO;
        static SlotDataAccessObject SlotDAO;

        static Controller* GetController();
        static void SafeDeleteController();
};

#endif // QAPPLICATIONGLOBAL_H

