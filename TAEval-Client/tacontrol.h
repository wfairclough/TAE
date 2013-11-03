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
    void getTas(QString view);
    void getTaskListForTa(QString view, QString uname);
    void getEvaluationListForTasks(QString view, QList<quint32> taskIds);
    void deleteTaskForTA(QString view, QString taskName, QString username);
    void addTaskForTa(QString view, QString uname, QString taskName, QString taskDescription, QString courseName, Semester::semester_t sem, int courseYear);
    void updateTaskAndEvaluation(QString view, Task* task, Evaluation* eval);

signals:
    
public slots:
    
};

#endif // TACONTROL_H
