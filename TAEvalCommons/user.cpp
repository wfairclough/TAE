#include "user.h"


QDataStream &operator <<(QDataStream &stream, const User &user)
{
    stream << user.getFirstName();
    stream << user.getLastName();
    stream << user.getUsername();

    return stream;
}


QDataStream &operator >>(QDataStream &stream, User &user)
{
    bool ok;
    QString str;

    stream >> str;
    user.setFirstName(str);

    stream >> str;
    user.setLastName(str);

    stream >> str;
    user.setUsername(str);

    return stream;
}

