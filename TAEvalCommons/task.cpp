#include "task.h"
#include <QDebug>

Task::Task(QObject *parent) :
    QObject(parent),
    id(-1),
    teachingAssistant(NULL),
    taSet(false)
{
}

QDataStream &operator <<(QDataStream &stream, const Task &task)
{
    stream << task.getIdString();
    stream << task.getName();
    stream << task.getDescription();

    if (task.hasTeachingAssistant()) {
        if (task.getTeachingAssistant() != NULL) {
            stream << QString("true");
            TeachingAssistant* ta = task.getTeachingAssistant();
            stream << *ta;
        } else {
            stream << QString("false");
        }

    } else {
        stream << QString("false");
    }

    qDebug() << "Task Oper<< ID" << task.getId() << task.getName() << task.getDescription();
    qDebug() << "Task Oper<< " << task.getIdString() << task.getName() << task.getDescription();

    return stream;
}


QDataStream &operator >>(QDataStream &stream, Task &task)
{
    QString name;
    QString description;
    QString aId;
    QString hasTa;

    stream >> aId;
    task.setId(aId.toUInt());

    stream >> name;
    task.setName(name);

    stream >> description;
    task.setDescription(description);

    stream >> hasTa;
    qDebug() << "HAS TA: " << hasTa;
    if (hasTa.compare(QString("true")) == 0) {
        TeachingAssistant* ta = new TeachingAssistant;
        stream >> *ta;
        qDebug() << "Task has TA: " << ta->getFirstName() << " " << ta->getLastName();
    } else {
        qDebug() << "Task has no TA";
    }

    qDebug() << "Task Oper>> Before " << aId << name << description;
    qDebug() << "Task Oper>> After " << task.getId() << task.getName() << task.getDescription();

    return stream;
}
