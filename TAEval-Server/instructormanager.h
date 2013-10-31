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


signals:

public slots:

};

#endif // INSTRUCTORMANAGER_H
