#ifndef APIWINDOW_H
#define APIWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "instructorcontrol.h"
#include "teachingassistant.h"
#include "instructor.h"
#include "task.h"

namespace Ui {
class ApiWindow;
}

class ApiWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApiWindow(QWidget *parent = 0);
    ~ApiWindow();

public slots:
    void recievedTaListForInstructor(QString view, QList<TeachingAssistant*> list);
    void recievedInstructorList(QString view,QList<Instructor*> list);
    void recievedTaList(QString view, QList<TeachingAssistant*> list);
    void recievedTaskListForTa(QString view, QList<Task*> list);
    void recievedDeleteTaskForTa(QString view, QList<Task*> list);
    void recievedAddTaskForTa(QString view, QList<Task*> list);

private slots:
    void handleNewTask();
    void handleEditTask();
    void handleDeleteTask();
    void handleAssignTask();
    void handleEvaluateTask();
    void handleViewTa();
    void handleViewCourse();
    void handleViewTask();

    void mtinstructorCellClicked(int currentRow, int currentCol);
    void mttaCellClicked(int currentRow, int currentCol);
    void mttaskCellClicked(int currentRow, int currentCol);
    void mtdeleteClicked();
    void mtcellItemChanged(QTableWidgetItem* item);

private:
    Ui::ApiWindow *ui;
    void enableDeleteButton();
    void disableDeleteButton();

    // Initialize the each of the Views
    void initCreateTaskView();
    void initEditTaskView();
    void initDeleteTaskView();
    void initAssignTaskView();
    void initEvaluateTask();
    void initViewTaView();
    void initViewCourseView();
    void initViewTaskView();

};

#endif // APIWINDOW_H
