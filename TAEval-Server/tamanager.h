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
    QList<Task *> deleteTaskForTa(Task* task, TeachingAssistant* ta);
    QList<Task *> addTaskForTa(Task* task, TeachingAssistant* ta);

signals:
    
public slots:
    
};

#endif // TAMANAGER_H
