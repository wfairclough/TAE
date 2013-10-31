#include "course.h"

Course::Course(QObject *parent) :
    QObject(parent)
{
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

    stream >> str;
    course.setName(str);

    stream >> str;
    course.setSemester(str);

    stream >> str;
    course.setYear(str);

    return stream;
}
