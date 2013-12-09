#ifndef INSTRUCTORMANAGER_H
#define INSTRUCTORMANAGER_H

#include <QObject>

#include <dataaccessmanager.h>


class InstructorManager : public DataAccessManager
{
    Q_OBJECT
public:
    explicit InstructorManager();
    QList<Instructor *> fetchAllInstructors();
    QList<TeachingAssistant *> fetchAllTeachingAssistanceForInstructor(Instructor* instructor);
    QList<Course *> fetchAllCoursesforInstructor(Instructor* Instructor);
    QList<TeachingAssistant *> fetchAllTeachingAssistanceForCourse(Course* course);

signals:

public slots:

};

#endif // INSTRUCTORMANAGER_H
