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

    Instructor* getCurrentInstructor() const { return instructor; }

    // Subscriber Implementations
    void updateTaskListForTaAndCourse(QList<Task*> list);
    void updateTaListForInstructor(QList<TeachingAssistant*> list);
    void updateCourseListForInstructor(QList<Course*> list);
    void updateAddTaskForTa(QList<Task*> list);
    void updateEvaluationListForTasks(QList<Evaluation*> list);

public slots:
    void currentCourseComboIndexChanged(int index);
    void taCellClicked(int row, int col);
    void taskCellClicked(int row, int col);
    
private:
    Ui::InstructorWindow *ui;
    Instructor* instructor;

    void initInstructorView();
    void selectCourse(Course* course);

    QMap<quint32, Task*> taskMap;
    QMap<quint32, Course*> courseMap;
    QMap<quint32, TeachingAssistant*> taMap;
};

#endif // INSTRUCTORWINDOW_H
