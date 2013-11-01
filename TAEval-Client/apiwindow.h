#ifndef APIWINDOW_H
#define APIWINDOW_H

#include <QMainWindow>
#include "instructorcontrol.h"
#include "teachingassistant.h"
#include "instructor.h"
#include "task.h"
#include "course.h" ////////////////////////ADDED //////////////

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
    void recievedCourseListForInstructor(QString view, QList<Course*> list); ///////////////////////////////////// ADDED

private slots:
    void handleNewTask();
    void handleEditTask();
    void handleDeleteTask();
    void handleAssignTask();
    void handleEvaluateTask();
    void handleViewTa();
    void handleViewCourse();
    void handleViewTask();

    void vcinstructorComboBoxChanged(QString profInfo);

private:
    Ui::ApiWindow *ui;
};

#endif // APIWINDOW_H
