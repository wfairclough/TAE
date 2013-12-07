#ifndef ABSTRACTSUBSCRIBER_H
#define ABSTRACTSUBSCRIBER_H

#include <teachingassistant.h>
#include <instructor.h>
#include <user.h>
#include <evaluation.h>
#include <task.h>
#include <course.h>
#include <QMap>
#include <QList>

class AbstractSubscriber
{
public:
    AbstractSubscriber();

    virtual void recievedLoginResponse(User* user) {}
    virtual void recievedFailedLoginResponse(QString error) {}
    virtual void connectionNetworkTimeout() {}
    virtual void connectionSuccess() {}
    virtual void updateTaListForInstructor(QList<TeachingAssistant*> list) {}
    virtual void updateCourseListForInstructor(QList<Course*> list) {}
    virtual void updateInstructorList(QList<Instructor*> list) {}
    virtual void updateTaList(QList<TeachingAssistant*> list) {}
    virtual void updateTaskListForTa(QList<Task*> list) {}
    virtual void updateTaskListForTaAndCourse(QList<Task*> list) {}
    virtual void updateAddTaskForTa(QList<Task*> list) {}
    virtual void updateEvaluationListForTasks(QList<Evaluation*> list) {}

};

#endif // ABSTRACTSUBSCRIBER_H
