#ifndef QAPPLICATIONGLOBAL_H
#define QAPPLICATIONGLOBAL_H
#include <QApplication>
#include "BidDAO.h"
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

        static QSqlDatabase CafeDB;
        static UserDAO UserDataAccessObject;
        static ShiftDAO ShiftDataAccessObject;
        static BidDAO BidDataAccessObject;
};

#endif // QAPPLICATIONGLOBAL_H

