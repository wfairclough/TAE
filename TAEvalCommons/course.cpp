#include "course.h"

Course::Course(QObject *parent) :
    QObject(parent)
{
}
 //////////////////////////////////Addded /////////////////////
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
    semester_t semester;
    QDate date;

    stream >> str;
    course.setName(str);

    stream >> semester;
    course.setSemester(semester);

    stream >> date;
    course.setYear(date);

    return stream;
}
