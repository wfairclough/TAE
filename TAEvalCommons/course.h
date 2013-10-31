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
    Course(QString cName, QString cSemester, QDate cYear); //////////////////ADDED ////////////////
    // Getter

    QDate getYear() const { return year;} ////////////////////////////////////// ADDED /////////////////////////////////////////////
    QString getName() const { return name; } ////////////////////////////////////// ADDED /////////////////////////////////////////////
  //  semester_t getSemesterType() const { return semester; }
    QString getSemesterType() const {return semester;}
    Instructor* getInstructor() { return instructor; }
    QList<TeachingAssistant*> getTeachingAssistants() { return taList; }

    // Setter
    void setInstructor(Instructor* i) { instructor = i; }
    void addTeachingAssistant(TeachingAssistant* ta) { taList << ta; }
    void setName(QString cName) { name = cName;} ////////////// ADDED /////////
   // void setSemester(semester_t cSemester) {semester = cSemester; } ///////// Added /////////
    void setSemester(QString cSemester) {semester = cSemester;}
    void setYear(QDate cYear) {year = cYear;} ///////// Added ///////////

    // Persistable
    QString getTableName() { return COURSE_TABLE_NAME; }


    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }
signals:
    
public slots:

private:
    QString name;
   // semester_t semester;
    QString semester;
    QDate year;
    Instructor* instructor;
    QList<TeachingAssistant*> taList;

};

#endif // COURSE_H
