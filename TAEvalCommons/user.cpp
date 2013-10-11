#include "user.h"


QDataStream &operator <<(QDataStream &stream, const User &user)
{
    stream << QString("" + user.getId());
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
    unsigned long id = str.toLong(&ok, 10);
    user.setId(id);

    stream >> str;
    user.setFirstName(str);

    stream >> str;
    user.setLastName(str);

    stream >> str;
    user.setUsername(str);

    return stream;
}

