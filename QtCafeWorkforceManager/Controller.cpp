#include "Controller.h"
#include "Commands.h"
#include "QApplicationGlobal.h"
#include "qcryptographichash.h"

#include <QString>


class Command;

ECommandResult Controller::HandleCommand(ICommand* Cmd)
{
    if(Update* UpdateCmd = dynamic_cast<Update*>(Cmd))
    {
        //HandleUpdate(arg1, arg2);
        //Serialize();
    }
    
    if(Authorize* AuthorizeCmd = dynamic_cast<Authorize*>(Cmd))
    {
        return HandleAuthorize(AuthorizeCmd);
    }
}

ECommandResult Controller::HandleAuthorize(Authorize* cmd)
{
    QByteArray passwordBytes = cmd->Password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPassword0x = QString(hashedPassword.toHex());

    bool bValidUser = false;
    int ValidUserIndex;
    for(int i = 0; i < QApplicationGlobal::Users.size(); i++)
    {

        if(cmd->Username.toStdString() == QApplicationGlobal::Users[i]->Username)
        {
            bValidUser = true;
            ValidUserIndex = i;
            i = QApplicationGlobal::Users.size(); // end loop
        }
    }

    if(bValidUser)
    {
        if(hashedPassword0x.toStdString() == QApplicationGlobal::Users[ValidUserIndex]->HashedPassword)
        {
            return ECommandResult::ECR_SUCCESS;
        }
    }
    return ECommandResult::ECR_FAILURE;
};
