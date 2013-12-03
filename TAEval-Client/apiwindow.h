#ifndef APIWINDOW_H
#define APIWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QMap>

#include "instructorcontrol.h"
#include "teachingassistant.h"
#include "instructor.h"
#include "task.h"
#include "course.h"
#include "evaluation.h"
#include "abstractsubscriber.h"


#define TASK_NAME_COL 0
#define TASK_DESCRIPTION_COL 1
#define TASK_EVAL_RATING_COL 2
#define TASK_EVAL_COMMENT_COL 3


#define MANAGE_TASK_VIEW "manageTaskView"
#define VIEW_COURSE_VIEW "viewCourseView"



namespace Ui {
class ApiWindow;
}

class ApiWindow : public QMainWindow, public AbstractSubscriber
{
    Q_OBJECT

public:
    explicit ApiWindow(QWidget *parent = 0);
    ~ApiWindow();

    void updateLogin(User* user);
    void updateTaListForInstructor(QList<TeachingAssistant*> list);
    void updateCourseListForInstructor(QList<Course*> list);
    void updateInstructorList(QList<Instructor*> list);
    void updateTaList(QList<TeachingAssistant*> list);
    void updateTaskListForTa(QList<Task*> list);
    void updateAddTaskForTa(QList<Task*> list);
    void updateEvaluationListForTasks(QList<Evaluation*> list);

public slots:
    void recievedTaListForInstructor(QString view, QList<TeachingAssistant*> list);
    void recievedInstructorList(QString view,QList<Instructor*> list);
    void recievedTaList(QString view, QList<TeachingAssistant*> list);
    void recievedTaskListForTa(QString view, QList<Task*> list);
    void recievedDeleteTaskForTa(QString view, QList<Task*> list);
    void recievedCourseListForInstructor(QString view, QList<Course*> list);

private slots:
    void handleManageTask();
    void handleViewCourse();

    void mtinstructorCellClicked(int currentRow, int currentCol);
    void mttaCellClicked(int currentRow, int currentCol);
    void mttaskCellClicked(int currentRow, int currentCol);
    void mtdeleteClicked();
    void mtupdateClicked();
    void mtaddTaskClicked();
    void mtcellItemChanged(QTableWidgetItem* item);
    void mttaskTableCellChanged(int row, int column);
    void vcinstructorComboBoxChanged(QString profInfo);

private:
    Ui::ApiWindow *ui;
    void mangeTaskSelectedStyle();
    void manageTaskDeselectedStyle();
    void viewCourseSelectedStyle();
    void viewCourseDeSelectedStyle();
    void updateViewStyles(QString selectedView);
    void enableButton(QPushButton*& button);
    void disableButton(QPushButton*& button);
    bool checkEvaluationRating(QString evalRating);
    bool validateTaskFields(QString name, QString description);

    // Initialize the each of the Views
    void initManageTaskView();
    void initViewCourseView();

    QMap<quint32, Task*> taskMap;
    QList<quint32> taskIds;

};

#endif // APIWINDOW_H
