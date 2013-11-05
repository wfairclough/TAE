#include "course.h"
#include <QDebug>

Course::Course(QObject *parent) :
    QObject(parent),
    semester(Semester::FALL),
    instructor(NULL),
    instructorSet(false)
{

}


QString Course::getSemesterTypeString() const {

    switch (getSemesterType()) {
    case Semester::FALL:
    {
        return QString("Fall");
        break;
    }
    case Semester::WINTER:
    {
        return QString("Winter");
        break;
    }
    case Semester::SUMMER:
    {
        return QString("Summer");
        break;
    }
    default:
        return QString("None");
        break;
    }
}


QDataStream &operator <<(QDataStream &stream, const Course &course)
{
    stream << course.getName();
    stream << QString::number(course.getSemesterTypeInt());
    stream << course.getYearString();

    if (course.hasInstructor()) {
        Instructor* instructor = course.getInstructor();
        if (instructor != NULL) {
            stream << QString("true");
            stream << *instructor;
        } else {
            stream << QString("false");
        }
    } else {
        stream << QString("false");
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
    course.setSemesterType(semType.toInt());

    stream >> year;
    course.setYear(year.toInt());

    stream >> hasInstructor;
    if (hasInstructor.compare(QString("true")) == 0) {
        qDebug() << " has Instructor true" << hasInstructor;
        Instructor* inst = new Instructor;
        stream >> *inst;
        course.setInstructor(inst);
    }

    return stream;
}
