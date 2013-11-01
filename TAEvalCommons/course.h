#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include <QMap>
#include <QDate>

#include <instructor.h>
#include <teachingassistant.h>
#include <persistable.h>

#define COURSE_TABLE_NAME "COURSE"

class Course : public QObject, public Persistable
{
    Q_OBJECT
//    Q_ENUMS(semester_t)
public:
/* note: commeting out and setting semester to be a string to fix issue with datasteam
    enum semester_t {
        FALL = 0,
        WINTER,
        SUMMER
    };
*/
    explicit Course(QObject *parent = 0);
    Course(QString cName, QString cSemester, QString cYear); //////////////////ADDED ////////////////
    // Getter

    QString getYear() const { return year;} ////////////////////////////////////// ADDED /////////////////////////////////////////////
    QString getName() const { return name; } ////////////////////////////////////// ADDED /////////////////////////////////////////////
    QString getSemesterType() const {return semester;}
    Instructor* getInstructor() { return instructor; }
    QList<TeachingAssistant*> getTeachingAssistants() { return taList; }

    // Setter
    void setInstructor(Instructor* i) { instructor = i; }
    void addTeachingAssistant(TeachingAssistant* ta) { taList << ta; }
    void setName(QString cName) { name = cName;} ////////////// ADDED /////////
    void setSemester(QString cSemester) {semester = cSemester;}
    void setYear(QString cYear) {year = cYear;} ///////// Added ///////////

    // Persistable
    QString getTableName() { return COURSE_TABLE_NAME; }


    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }
signals:
    
public slots:

private:
    QString name;
    QString semester;
    QString year;
    Instructor* instructor;
    QList<TeachingAssistant*> taList;

};

// Operator Override
QDataStream &operator <<(QDataStream &stream, const Course &user);
QDataStream &operator >>(QDataStream &stream, Course &user);

#endif // COURSE_H
