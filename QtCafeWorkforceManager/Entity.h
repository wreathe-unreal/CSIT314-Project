#ifndef ENTITY_H
#define ENTITY_H

#include <QSqlDatabase>


class Entity
{
public:
    Entity(const QString& path);
private:
    QSqlDatabase CafeDB;
};

#endif // ENTITY_H
