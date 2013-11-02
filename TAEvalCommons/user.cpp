#include "user.h"
#include <QDebug>

QDataStream &operator <<(QDataStream &stream, const User &user)
{
    qDebug() << "STARTING FOR SURE" << &user;
    qDebug() << "start user proccessing " << user.getId();
    stream << user.getIdString();
    qDebug() << "id str " << user.getIdString();
    stream << user.getFirstName();
    qDebug() << "first " << user.getFirstName();
    stream << user.getLastName();
    qDebug() << "last " << user.getLastName();
    stream << user.getUsername();
    qDebug() << "user " << user.getUsername();

    return stream;
}


QDataStream &operator >>(QDataStream &stream, User &user)
{
    QString str;

    stream >> str;
    user.setId(str.toUInt()); // Convert String id to quint32

    stream >> str;
    user.setFirstName(str);

    stream >> str;
    user.setLastName(str);

    stream >> str;
    user.setUsername(str);

    return stream;
}

