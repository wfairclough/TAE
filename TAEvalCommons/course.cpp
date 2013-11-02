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
    qDebug() << "Course Name " << course.getName();
    stream << course.getName();
    qDebug() << "Course Sem Type " << course.getSemesterTypeInt();
    stream << course.getSemesterTypeInt();
    qDebug() << "Course Year " << course.getYearString();
    stream << course.getYearString();

    if (course.hasInstructor()) {
        qDebug() << "hasInstructor";
        Instructor* instructor = course.getInstructor();
        if (instructor != NULL) {
            qDebug() << "Instructor is not null";
            stream << QString("true");
            stream << *instructor;
            qDebug() << "Added instructor";
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
