#include "tawindow.h"
#include "ui_tawindow.h"
#include "connectionclient.h"
#include "tacontrol.h"



TaWindow::TaWindow(TeachingAssistant* user, QWidget *parent) :
    teachingAssistant(user),
    QMainWindow(parent),
    ui(new Ui::TaWindow)
{
    ui->setupUi(this);
    connect(ui->courseComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(currentCourseComboIndexChanged(int)));

    initManageTaskView();
    setWindowTitle("Teaching Assistant: " + user->getFullName());

    ConnectionClient::getInstance().subscribe(this);

    TaControl tc;
    tc.getCoursesForTeachingAssistant(getCurrentTa());
}

void TaWindow::initManageTaskView(){
    ui->TW_TaskSelect->resizeColumnsToContents();
    ui->TW_TaskSelect->horizontalHeader()->setResizeMode(TASK_NAME_COL, QHeaderView::Stretch);
    ui->TW_TaskSelect->horizontalHeader()->setResizeMode(TASK_EVALUATED_COL, QHeaderView::ResizeToContents);
    ui->TW_TaskSelect->setStyleSheet("color:#333");
}

TaWindow::~TaWindow()
{
    delete ui;
}

void TaWindow::updateCourseListForTa(QList<Course*> list) {
    courseMap.clear();

    int index = 0;
    foreach(Course* course, list) {
        courseMap.insert(index++, course);
        ui->courseComboBox->addItem(course->getFullCourseName());
    }
}

/**
 * @brief TaWindow::updateTaskListForTaAndCourse
 * @param list
 */
void TaWindow::updateTaskListForTaAndCourse(QList<Task*> list) {
    ui->TW_TaskSelect->setRowCount(0); // TW_TaskSelect is the widget in ta ui to view / select task

    qDebug() << "Task List size: " << list.size();

    taskMap.clear();
    foreach(Task* task, list){
        int row = ui->TW_TaskSelect->rowCount();
        taskMap.insert(row, task);

        qDebug() << "Adding Task to Table: " << task->getName();

        ui->TW_TaskSelect->insertRow(row);
        ui->TW_TaskSelect->setItem(row, TASK_NAME_COL, new QTableWidgetItem(task->getName()));
        if (task->hasEvaluation()) {
            ui->TW_TaskSelect->setItem(row, TASK_EVALUATED_COL, new QTableWidgetItem("Evaluated"));
        } else {
            ui->TW_TaskSelect->setItem(row, TASK_EVALUATED_COL, new QTableWidgetItem(QString("No Evaluation")));
        }

    }
}


void TaWindow::selectCourse(Course* course) {

    if (course != NULL) {
        TaControl tc;
        tc.getTaskListForTaAndCourse(getCurrentTa(), course);
    }

}


void TaWindow::currentCourseComboIndexChanged(int index) {
    selectCourse(courseMap.value(index));
}

