#include "task.h"

Task::Task(QObject *parent) :
    QObject(parent),
    id(-1)
{
}

QDataStream &operator <<(QDataStream &stream, const Task &task)
{
    stream << task.getIdString();
    stream << task.getName();
    stream << task.getDescription();

    return stream;
}


QDataStream &operator >>(QDataStream &stream, Task &task)
{
    QString str;
    QString aId;

    stream >> aId;
    task.setId(aId.toUInt());

    stream >> str;
    task.setName(str);

    stream >> str;
    task.setDescription(str);

    return stream;
}
