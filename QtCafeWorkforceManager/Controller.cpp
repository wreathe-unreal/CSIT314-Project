#include "Controller.h"
#include "Commands.h"
#include "QApplicationGlobal.h"
#include "qcryptographichash.h"

#include <QString>


class Command;

Response Controller::HandleCommand(ICommand* cmd)
{
    Response response = Response(ECommandResult::ECR_FAILURE);

    if(cmd->GetType() == ECommandType::ECT_Update)
    {
        //HandleUpdate(arg1, arg2);
    }

    if(cmd->GetType() == ECommandType::ECT_Authorize)
    {
        response = Response(HandleAuthorize(dynamic_cast<Authorize*>(cmd)));
    }

    delete cmd;
    cmd = nullptr;
    return response; //return fail if no valid command
}

Response Controller::HandleAuthorize(Authorize* cmd)
{
    QByteArray passwordBytes = cmd->Password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());

    return QApplicationGlobal::UserDAO.Auth(cmd->Username, hashedPasswordHex);
};
