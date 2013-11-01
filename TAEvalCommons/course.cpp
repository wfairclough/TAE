#include "course.h"

Course::Course(QObject *parent) :
    QObject(parent)
{
}
 //////////////////////////////////Addded /////////////////////

Course::Course(QString cName, QString cSemester, QString cYear)
{
    setName(cName);
    setSemester(cSemester);
    setYear(cYear);
}

QDataStream &operator <<(QDataStream &stream, const Course &course)
{
    stream << course.getName();
    stream << course.getSemesterType();
    stream << course.getYear();

    return stream;
}


QDataStream &operator >>(QDataStream &stream, Course &course)
{
    bool ok;
    QString str;
    QString date;

    stream >> str;
    course.setName(str);

    stream >> str;
    course.setSemester(str);

    stream >> date;
    course.setYear(date);

    return stream;
}
