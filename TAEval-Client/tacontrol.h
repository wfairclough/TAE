#ifndef TACONTROL_H
#define TACONTROL_H

#include <QObject>
#include <course.h>
#include <task.h>

class TaControl : public QObject
{
    Q_OBJECT
public:
    explicit TaControl(QObject *parent = 0);
    void getTas(QString view);
    void getTaskListForTa(QString view, QString uname);
    void deleteTaskForTA(QString view, QString taskName, QString username);
    void addTaskForTa(QString view, QString uname, QString taskName, QString taskDescription, QString courseName, Semester::semester_t sem, int courseYear);
    void updateTask(Task* task);

signals:
    
public slots:
    
};

#endif // TACONTROL_H
