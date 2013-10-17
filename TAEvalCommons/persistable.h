#ifndef PERSISTABLE_H
#define PERSISTABLE_H

#include <QString>
#include <QMap>

class Persistable
{
public:
    virtual QString getTableName() = 0;
    virtual QMap<QString, QString> getTuple() = 0;
};

#endif // PERSISTABLE_H
