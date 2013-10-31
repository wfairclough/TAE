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
    QList<Task *> deleteTaskForTa(Task* task, TeachingAssistant* ta);
    QList<Task *> addTaskForCourse(Task* task, Course* course);
    Evaluation* fetchEvaluationForTask(Task* task);
    bool addEvaluationToTask(Evaluation* eval, Task* task);

signals:
    
public slots:
    
};

#endif // TAMANAGER_H
