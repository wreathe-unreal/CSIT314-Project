#ifndef RESPONSE_H
#define RESPONSE_H
#include <QJsonDocument>
#include <QJsonObject>
#include "Enums.h"
#include <QString>
class Response
{
    public:
        ECommandResult Result;
        QString Json;

        Response(ECommandResult ecr)
        {
            Json = "";
            Result = ecr;
        }
        Response(QString json)
        {
            Json = json;
            Result = ECommandResult::ECR_SUCCESS;
        }
        Response(ECommandResult ecr, QJsonObject json)
        {
            Json = QJsonDocument(json).toJson();
            Result = ecr;
        }

        ECommandResult getResult() const;
        void setResult(ECommandResult newResult);
        QJsonObject getJsonObject() const;
        void setJson(const QString &newJson);
};

inline QJsonObject Response::getJsonObject() const
{
        return QJsonDocument::fromJson(Json.toUtf8()).object();
}

inline ECommandResult Response::getResult() const
{
        return Result;
}



#endif // RESPONSE_H
