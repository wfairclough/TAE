#ifndef TAMANAGER_H
#define TAMANAGER_H

#include <QObject>

#include <dataaccessmanager.h>


class TaManager : public DataAccessManager
{
    Q_OBJECT
public:
    explicit TaManager();
    QList<TeachingAssistant *> fetchAllTas();
    QList<Task *> fetchAllTasksForTeachingAssistance(TeachingAssistant* ta);
    QList<Task *> fetchAllTasksForCourse(Course* course);
    QList<Evaluation*> fetchEvaluationsForTasks(QList<Task*> tasks);
    QList<Task *> addTaskForTACourse(Task* task, QString taUsername, Course* course);
    QList<Task *> fetchTasksForTaAndCourse(TeachingAssistant* teachingAssistant, Course* course);
    QList<Course *> fetchAllCoursesforTeachingAssistant(TeachingAssistant* ta);
    Evaluation* fetchEvaluationForTask(Task* task);
    bool deleteEvaluationForTask(int taskId);
    bool deleteTask(Task* task);
    Task* updateTaskAndEvaluation(Task* task, QString iName, QString taName);

signals:
    
public slots:
    
};

#endif // TAMANAGER_H
