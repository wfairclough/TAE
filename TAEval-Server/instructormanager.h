#ifndef INSTRUCTORMANAGER_H
#define INSTRUCTORMANAGER_H

#include <QObject>
#include <QtSql>

#include <instructor.h>
#include <teachingassistant.h>
#include <course.h>
#include <task.h>
#include <evaluation.h>

class InstructorManager : public QObject
{
    Q_OBJECT
public:
    explicit InstructorManager(QObject *parent = 0);
    QList<Instructor *> fetchAllInstructors();
    QList<TeachingAssistant *> fetchAllTeachingAssistanceForInstructor(Instructor* instructor);
    QList<Course *> fetchAllCoursesforInstructor(Instructor* Instructor);  /////////////////////////////////////////Added //////////////////////////////////////


signals:

public slots:

};

#endif // INSTRUCTORMANAGER_H
