#include "Commands.h"
#include "QApplicationGlobal.h"
#include "qcryptographichash.h"
#include <QString>

EUserProfile AuthorizeController::Execute()
{
    QByteArray passwordBytes = Password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());

    return QApplicationGlobal::UserDAO.Authorize(Username, hashedPasswordHex);
}


