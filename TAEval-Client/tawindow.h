#ifndef TAWINDOW_H
#define TAWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "teachingassistant.h"
#include "task.h"
#include "course.h"
#include "abstractsubscriber.h"

#define TASK_NAME_COL 0
#define TASK_EVALUATED_COL 1

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
    
    TeachingAssistant* getCurrentTa() const { return teachingAssistant; }

    // Subscriber Implementations
    void updateTaskListForTaAndCourse(QList<Task*> list);
    void updateCourseListForTa(QList<Course*> list);

public slots:
    void currentCourseComboIndexChanged(int index);

private:
    void selectCourse(Course* course);

    Ui::TaWindow *ui;
    TeachingAssistant* teachingAssistant;


    void initManageTaskView();

    QMap<quint32, Task*> taskMap;
    QMap<quint32, Course*> courseMap;

};

#endif // TAWINDOW_H
