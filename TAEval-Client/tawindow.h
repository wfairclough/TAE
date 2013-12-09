#ifndef TAWINDOW_H
#define TAWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "teachingassistant.h"
#include "task.h"
#include "course.h"
#include "abstractsubscriber.h"

#define TASK_INFO_VIEW_INDEX 1

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
    
    // Getters
    TeachingAssistant* getCurrentTa() const { return teachingAssistant; }
    Task* getCurrentTask() const { return currentTask; }


    // Setters
    void setCurrentTask(Task* task) {currentTask = task;}

    // Subscriber Implementations
    void updateTaskListForTaAndCourse(QList<Task*> list);
    void updateCourseListForTa(QList<Course*> list);
    void connectionDisconnected();

private slots:
    void currentCourseComboIndexChanged(int index);
    void refreshButtonReleased();
    void taskCellClicked(int row, int col);

    void logout();
    void quit();

private:
    void selectCourse(Course* course);
    void selectTask(Task* task);

    void closeWindow();

    Ui::TaWindow *ui;
    TeachingAssistant* teachingAssistant;
    Task* currentTask;


    void initManageTaskView();

    QMap<quint32, Task*> taskMap;
    QMap<quint32, Course*> courseMap;

};

#endif // TAWINDOW_H
