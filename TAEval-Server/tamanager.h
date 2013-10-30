#ifndef TAMANAGER_H
#define TAMANAGER_H

#include <QObject>
#include <QtSql>

#include <instructor.h>
#include <teachingassistant.h>
#include <course.h>
#include <task.h>
#include <evaluation.h>

class TaManager : public QObject
{
    Q_OBJECT
public:
    explicit TaManager(QObject *parent = 0);
    QList<TeachingAssistant *> fetchAllTas();
    QList<Task *> fetchAllTasksForTeachingAssistance(TeachingAssistant* ta);
    
signals:
    
public slots:
    
};

#endif // TAMANAGER_H
