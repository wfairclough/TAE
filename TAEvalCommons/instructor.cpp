#include "instructor.h"

Instructor::Instructor(QObject *parent) :
    QObject(parent)
{
}


Instructor::Instructor(unsigned long idArg, QString fName, QString lName, QString uName)
{
    setId(idArg);
    setFirstName(fName);
    setLastName(lName);
    setUsername(uName);
}



QDataStream &operator <<(QDataStream &stream, const Instructor &user)
{

    stream << QString("" + user.getId());
    stream << user.getFirstName();
    stream << user.getLastName();
    stream << user.getUsername();

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Instructor &user)
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
