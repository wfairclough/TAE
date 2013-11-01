#include "course.h"

Course::Course(QObject *parent) :
    QObject(parent)
{

}


QDataStream &operator <<(QDataStream &stream, const Course &course)
{
    stream << course.getName();
    stream << course.getSemesterTypeIntStr();
    stream << course.getYearString();

    if (course.getInstructor() != NULL) {
        stream << QString("true");
        stream << *course.getInstructor();
    }

    return stream;
}


QDataStream &operator >>(QDataStream &stream, Course &course)
{
    QString name;
    QString semType;
    QString year;
    QString hasInstructor;

    stream >> name;
    course.setName(name);

    stream >> semType;
    course.setSemesterType(Semester::semester_t(semType.toUInt()));

    stream >> year;
    course.setYear(year.toInt());

    stream >> hasInstructor;
    if (hasInstructor.compare(QString("true")) == 0) {
        Instructor* inst = new Instructor;
        stream >> *inst;
        course.setInstructor(inst);
    }


    return stream;
}
