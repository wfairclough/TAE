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
    Evaluation* fetchEvaluationForTask(Task* task);
    bool deleteEvaluationForTask(int taskId, Evaluation* eval);
    bool deleteEvaluation(Evaluation* eval);
    bool deleteTask(Task* task);
    bool updateTaskAndEvaluation(Task* task);

signals:
    
public slots:
    
};

#endif // TAMANAGER_H
