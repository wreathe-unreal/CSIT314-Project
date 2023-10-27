#ifndef QAPPLICATIONGLOBAL_H
#define QAPPLICATIONGLOBAL_H
#include <QApplication>
#include "Controller.h"
#include "SlotDAO.h"
#include "UserDAO.h"
#include "BidDAO.h"
#include <QSqlDatabase>

#define DATABASE QApplicationGlobal::CafeDB

class QApplicationGlobal : public QApplication
{
    Q_OBJECT

    public:
        QApplicationGlobal(int &argc, char **argv);

        ~QApplicationGlobal()
        {
            this->CafeDB.close();
        };

        static int CurrentUserID;
        static QString CurrentUsername;

        static QSqlDatabase CafeDB;

        static UserDataAccessObject UserDAO;
        static SlotDataAccessObject SlotDAO;
        static BidDataAccessObject BidDAO;

};

#endif // QAPPLICATIONGLOBAL_H

