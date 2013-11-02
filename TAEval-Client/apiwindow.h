#ifndef APIWINDOW_H
#define APIWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMap>

#include "instructorcontrol.h"
#include "teachingassistant.h"
#include "instructor.h"
#include "task.h"
#include "course.h"

#define TASK_NAME_COL 0
#define TASK_DESCRIPTION_COL 1


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
    void recievedCourseListForInstructor(QString view, QList<Course*> list);

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
    void vcinstructorComboBoxChanged(QString profInfo);
    void taskTableCellChanged(int row, int column);

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

    QMap<quint32, Task*> taskMap;

};

#endif // APIWINDOW_H
