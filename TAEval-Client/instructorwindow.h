#ifndef INSTRUCTORWINDOW_H
#define INSTRUCTORWINDOW_H

#include <QMainWindow>
#include "abstractsubscriber.h"
#include <instructor.h>
#include <teachingassistant.h>
#include <course.h>
#include <task.h>
#include <evaluation.h>

#define TASK_INFO_HELP_INDEX 0
#define TASK_INFO_VIEW_INDEX 1
#define TASK_INFO_EDIT_INDEX 2
#define TASK_INFO_NEW_INDEX 3

#define TA_COL_NAME 0
#define TA_COL_RATING 1
#define TASK_COL_NAME 0
#define TASK_COL_EVALUATED 1

namespace Ui {
class InstructorWindow;
}

class InstructorWindow : public QMainWindow, public AbstractSubscriber
{
    Q_OBJECT
    
public:
    explicit InstructorWindow(Instructor* user, QWidget *parent = 0);
    ~InstructorWindow();

    // Getters
    Instructor* getCurrentInstructor() const { return instructor; }
    TeachingAssistant* getCurrentTa() const { return currentTa; }
    Task* getCurrentTask() const { return currentTask; }
    Course* getCurrentCourse() const { return currentCourse; }

    // Setters
    void setCurrentTa(TeachingAssistant* ta) {currentTa = ta;}
    void setCurrentTask(Task* task) {currentTask = task;}
    void setCurrentCourse(Course* course) { currentCourse = course; }

    // Subscriber Implementations
    void updateTaskListForTaAndCourse(QList<Task*> list);
    void updateTaListForInstructor(QList<TeachingAssistant*> list);
    void updateCourseListForInstructor(QList<Course*> list);
    void updateTask(Task *task);
    void connectionDisconnected();

private slots:
    void currentCourseComboIndexChanged(int index);
    void editRatingComboIndexChanged(int index);
    void taCellClicked(int row, int col);
    void taskCellClicked(int row, int col);
    void switchToEditView();
    void switchToNewView();
    void cancelEdit();
    void deleteTask();
    void saveTask();

    void logout();
    void quit();

private:
    Ui::InstructorWindow *ui;
    Instructor* instructor;
    TeachingAssistant* currentTa;
    Task* currentTask;
    Course* currentCourse;

    void closeWindow();
    void initInstructorView();
    void setupEditRatingText(QString firstItem);
    void selectCourse(Course* course);
    void selectTa(TeachingAssistant* ta);
    void selectTask(Task* task);

    QMap<quint32, Task*> taskMap;
    QMap<quint32, Course*> courseMap;
    QMap<quint32, TeachingAssistant*> taMap;
};

#endif // INSTRUCTORWINDOW_H
