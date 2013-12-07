#ifndef TACONTROL_H
#define TACONTROL_H

#include <QObject>
#include <course.h>
#include <task.h>
#include <evaluation.h>
#include <QList>

class TaControl : public QObject
{
    Q_OBJECT
public:
    explicit TaControl(QObject *parent = 0);
    void getTas();
    void getTaskListForTa(QString uname);
    void getEvaluationListForTasks(QList<quint32> taskIds);
    void deleteTask(Task* task);
    void addTaskForTa(QString uname, QString taskName, QString taskDescription, QString courseName, Semester::semester_t sem, int courseYear);
    void updateTaskAndEvaluation(Task* task, QString iName, QString taName);
    void getCoursesForTeachingAssistant(TeachingAssistant* ta);
    void getTaskListForTaAndCourse(TeachingAssistant* ta, Course* course);

signals:
    
public slots:
    
};

#endif // TACONTROL_H
