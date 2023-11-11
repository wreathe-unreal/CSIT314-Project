#ifndef QAPPLICATIONGLOBAL_H
#define QAPPLICATIONGLOBAL_H
#include <QApplication>
#include "Controller.h"
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

};

#endif // QAPPLICATIONGLOBAL_H

