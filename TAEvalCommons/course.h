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
    Q_ENUMS(semester_t)
public:

    enum semester_t {
        FALL = 0,
        WINTER,
        SUMMER
    };

    explicit Course(QObject *parent = 0);
    
    // Getter
    semester_t getSemesterType() { return semester; }
    Instructor* getInstructor() { return instructor; }
    QList<TeachingAssistant*> getTeachingAssistants() { return taList; }

    // Setter
    void setInstructor(Instructor* i) { instructor = i; }
    void addTeachingAssistant(TeachingAssistant* ta) { taList << ta; }

    // Persistable
    QString getTableName() { return COURSE_TABLE_NAME; }


    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }
signals:
    
public slots:

private:
    QString name;
    semester_t semester;
    QDate year;
    Instructor* instructor;
    QList<TeachingAssistant*> taList;

};

#endif // COURSE_H
