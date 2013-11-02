#include "course.h"
#include <QDebug>

Course::Course(QObject *parent) :
    QObject(parent),
    semester(Semester::FALL),
    instructor(NULL)
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
    qDebug() << "5";
    stream << course.getName();
    stream << course.getSemesterTypeInt();
    stream << course.getYearString();

    qDebug() << "6";

    if (course.hasInstructor()) {
        Instructor* instructor = course.getInstructor();
        if (instructor != NULL) {
            stream << QString("true");
            stream << *instructor;
        }
    }

    return stream;
}


QDataStream &operator >>(QDataStream &stream, Course &course)
{
    qDebug() << "1";
    QString name;
    QString semType;
    QString year;
    QString hasInstructor;

    qDebug() << "2";

    stream >> name;
    course.setName(name);

    qDebug() << "3";

    stream >> semType;
    course.setSemesterType(semType.toUInt());

    qDebug() << "4";

    stream >> year;
    course.setYear(year.toInt());

    qDebug() << "This is the spot";

    stream >> hasInstructor;
    if (hasInstructor.compare(QString("true")) == 0) {
        qDebug() << " has Instructor true" << hasInstructor;
        Instructor* inst = new Instructor;
        stream >> *inst;
        course.setInstructor(inst);
    }

    return stream;
}
