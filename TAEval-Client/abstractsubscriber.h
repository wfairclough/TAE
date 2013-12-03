#ifndef ABSTRACTSUBSCRIBER_H
#define ABSTRACTSUBSCRIBER_H

#include <teachingassistant.h>
#include <instructor.h>
#include <user.h>
#include <evaluation.h>
#include <task.h>
#include <course.h>

class AbstractSubscriber
{
public:
    AbstractSubscriber();

    virtual void updateLogin(User* user) = 0;
    virtual void updateTaListForInstructor(QList<TeachingAssistant*> list) = 0;
    virtual void updateCourseListForInstructor(QList<Course*> list) = 0;
    virtual void updateInstructorList(QList<Instructor*> list) = 0;
    virtual void updateTaList(QList<TeachingAssistant*> list) = 0;
    virtual void updateTaskListForTa(QList<Task*> list) = 0;
    virtual void updateAddTaskForTa(QList<Task*> list) = 0;
    virtual void updateEvaluationListForTasks(QList<Evaluation*> list) = 0;

};

#endif // ABSTRACTSUBSCRIBER_H
