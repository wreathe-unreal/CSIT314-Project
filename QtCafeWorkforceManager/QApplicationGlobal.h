#ifndef QAPPLICATIONGLOBAL_H
#define QAPPLICATIONGLOBAL_H
#include "UserTypes.h"
#include <QApplication>
#include "Controller.h"

class QApplicationGlobal : public QApplication
{
    Q_OBJECT

    public:
        QApplicationGlobal(int &argc, char **argv);
        ~QApplicationGlobal()
        {
            for(auto u : Users)
            {
                delete u;
            }
            for(auto s : Shifts)
            {
                delete s;
            }
        }
        // Add other methods or member variables you need

        static std::vector<User*> Users;
        static std::vector<Shift*> Shifts;
        static Controller CmdController;
};

#endif // QAPPLICATIONGLOBAL_H

