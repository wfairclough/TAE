#include "task.h"
#include <QDebug>

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

    qDebug() << "Task Oper<< ID" << task.getId() << task.getName() << task.getDescription();
    qDebug() << "Task Oper<< " << task.getIdString() << task.getName() << task.getDescription();

    return stream;
}


QDataStream &operator >>(QDataStream &stream, Task &task)
{
    QString name;
    QString description;
    QString aId;

    stream >> aId;
    task.setId(aId.toUInt());

    stream >> name;
    task.setName(name);

    stream >> description;
    task.setDescription(description);

    qDebug() << "Task Oper>> Before " << aId << name << description;
    qDebug() << "Task Oper>> After " << task.getId() << task.getName() << task.getDescription();

    return stream;
}
