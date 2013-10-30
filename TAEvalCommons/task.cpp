#include "task.h"

Task::Task(QObject *parent) :
    QObject(parent)
{
}

QDataStream &operator <<(QDataStream &stream, const Task &user)
{
    stream << user.getName();
    stream << user.getDescription();

    return stream;
}


QDataStream &operator >>(QDataStream &stream, Task &user)
{
    bool ok;
    QString str;

    stream >> str;
    user.setName(str);

    stream >> str;
    user.setDescription(str);

    return stream;
}
