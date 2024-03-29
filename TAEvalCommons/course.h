#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include <QMap>
#include <QDate>

#include <instructor.h>
#include <teachingassistant.h>
#include <persistable.h>

#define COURSE_TABLE_NAME "COURSE"

namespace Semester {
    enum semester_t {
        WINTER = 0,
        SUMMER,
        FALL
    };
}


class Course : public QObject, public Persistable
{
    Q_OBJECT
//    Q_ENUMS(semester_t)
public:
    explicit Course(QObject *parent = 0);
    Course(QString cName, QString cSemester, QString cYear);

    // Getter
    Semester::semester_t getSemesterType() const { return semester; }
    QString getSemesterTypeString() const;
    int getSemesterTypeInt() const { return semester; }
    int getYear() const { return year; }
    QString getYearString() const { return QString::number(year); }
    QString getName() const { return name; }
    Instructor* getInstructor() const { return instructor; }
    QList<TeachingAssistant*> getTeachingAssistants() const { return taList; }
    bool hasInstructor() const { return instructorSet; }
    QString getFullCourseName() const { return getName() + " " + getSemesterTypeString() + getYearString(); }

    // Setter
    void setInstructor(Instructor* i) { instructor = i; instructorSet = true; }
    void addTeachingAssistant(TeachingAssistant* ta) { taList << ta; }
    void setName(QString aName) { name = aName; }
    void setSemesterType(Semester::semester_t sem) { semester = sem; }
    void setSemesterType(int sem) { semester = static_cast<Semester::semester_t>(sem); }
    void setYear(int y) { year = y; }


    static Semester::semester_t semesterTypeForString(QString value) {
        value = value.toLower();

        if (value.compare(QString("fall"))) {
            return Semester::FALL;
        } else if (value.compare(QString("winter"))) {
            return Semester::WINTER;
        } else if (value.compare(QString("summer"))) {
            return Semester::SUMMER;
        }
        return Semester::FALL;
    }


    // Persistable
    QString getTableName() { return COURSE_TABLE_NAME; }


    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }
signals:
    
public slots:

private:
    bool instructorSet;
    QString name;
    Semester::semester_t semester;
    int year;
    Instructor* instructor;
    QList<TeachingAssistant*> taList;

};

QDataStream &operator <<(QDataStream &stream, const Course &course);
QDataStream &operator >>(QDataStream &stream, Course &course);

#endif // COURSE_H
