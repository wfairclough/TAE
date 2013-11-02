#include "user.h"


QDataStream &operator <<(QDataStream &stream, const User &user)
{
    stream << user.getIdString();
    stream << user.getFirstName();
    stream << user.getLastName();
    stream << user.getUsername();

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

