#include "Controller.h"
#include "Commands.h"
#include "QApplicationGlobal.h"
#include "qcryptographichash.h"

#include <QString>


class Command;

ECommandResult Controller::HandleCommand(ICommand* cmd)
{
    ECommandResult result = ECommandResult::ECR_FAILURE;

    if(Update* UpdateCmd = dynamic_cast<Update*>(cmd))
    {
        //HandleUpdate(arg1, arg2);
    }

    if(Authorize* AuthorizeCmd = dynamic_cast<Authorize*>(cmd))
    {
        result = HandleAuthorize(AuthorizeCmd);
    }

    delete cmd;
    cmd = nullptr;
    return result; //return fail if no valid command
}

ECommandResult Controller::HandleAuthorize(Authorize* cmd)
{
    QByteArray passwordBytes = cmd->Password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPassword0x = QString(hashedPassword.toHex());

    return QApplicationGlobal::UserDAO.Auth(cmd->Username, hashedPassword0x);
};
