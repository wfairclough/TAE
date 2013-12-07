#ifndef TAWINDOW_H
#define TAWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "teachingassistant.h"
#include "task.h"
#include "course.h"
#include "abstractsubscriber.h"

#define TASK_NAME_COL 0
#define TASK_DESCRIPTION_COL 1
#define TASK_EVAL_RATING_COL 2
#define TASK_EVAL_COMMENT_COL 3

#define MANAGE_TASK_VIEW "manageTaskView"
#define VIEW_COURSE_VIEW "viewCourseView"

namespace Ui {
class TaWindow;
}

class TaWindow : public QMainWindow, public AbstractSubscriber
{
    Q_OBJECT
    
public:
    explicit TaWindow(TeachingAssistant* user, QWidget *parent = 0);
    ~TaWindow();
    
    void updateTaskListForTa(QList<Task*> list);
    void updateTaskListForTaAndCourse(QList<Task*> list);
    // ADD remaining calls to abstract subsciber here //

public slots:
    void currentCourseComboIndexChanged();
    void recievedTaskListForTa(QString view, QList<Task*> list);

private:
    void selectCourse(Course* course);

    Ui::TaWindow *ui;
    TeachingAssistant* teachingAssistant;


    void initManageTaskView();

    QMap<quint32, Task*> taskMap;
    QList<quint32> taskId;
};

#endif // TAWINDOW_H
