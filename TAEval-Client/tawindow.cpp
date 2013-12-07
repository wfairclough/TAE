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

    initManageTaskView();
    setWindowTitle("Teaching Assistant: " + user->getFullName());
}

void TaWindow::initManageTaskView(){

    ui->TW_TaskSelect->resizeColumnsToContents();
    ui->TW_TaskSelect->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
    ui->TW_TaskSelect->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->TW_TaskSelect->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);
    ui->TW_TaskSelect->horizontalHeader()->setResizeMode(3, QHeaderView::Stretch);
    ui->TW_TaskSelect->setStyleSheet("color:#333");
}

TaWindow::~TaWindow()
{
    delete ui;
}


/**
 * @brief TaWindow::updateTaskListForTa Subscriber method to get the updated task list
 * @param list
 */
void TaWindow::updateTaskListForTa(QList<Task*> list) {
    ui->TW_TaskSelect->setRowCount(0); // TW_TaskSelect is the widget in ta ui to view / select task

    taskMap.clear();
    foreach(Task* task, list){
        int row = ui->TW_TaskSelect->rowCount();
        taskMap.insert(row, task);

        ui->TW_TaskSelect->insertRow(row);
        ui->TW_TaskSelect->setItem(row, TASK_NAME_COL, new QTableWidgetItem(task->getName()));
        ui->TW_TaskSelect->setItem(row, TASK_DESCRIPTION_COL, new QTableWidgetItem(task->getDescription()));
        if (task->hasEvaluation()) {
            ui->TW_TaskSelect->setItem(row, TASK_EVAL_RATING_COL, new QTableWidgetItem(task->getEvaluation()->getRatingString()));
            ui->TW_TaskSelect->setItem(row, TASK_EVAL_COMMENT_COL, new QTableWidgetItem(task->getEvaluation()->getComment()));
        } else {
            ui->TW_TaskSelect->setItem(row, TASK_EVAL_RATING_COL, new QTableWidgetItem(Evaluation::ratingForEnum(RATING::NONE)));
            ui->TW_TaskSelect->setItem(row, TASK_EVAL_COMMENT_COL, new QTableWidgetItem(QString("")));
        }

    }

}

void TaWindow::updateTaskMapForTa(QMap<Course*, Task*> courseTaskMap) {
    ui->TW_TaskSelect->setRowCount(0); // TW_TaskSelect is the widget in ta ui to view / select task

    foreach(Course* course , courseTaskMap.keys()) {
        QVariant userData;
        ui->courseComboBox->addItem(course->getName());
    }

//    taskMap.clear();
//    foreach(Task* task, list){
//        int row = ui->TW_TaskSelect->rowCount();
//        taskMap.insert(row, task);

//        ui->TW_TaskSelect->insertRow(row);
//        ui->TW_TaskSelect->setItem(row, TASK_NAME_COL, new QTableWidgetItem(task->getName()));
//        ui->TW_TaskSelect->setItem(row, TASK_DESCRIPTION_COL, new QTableWidgetItem(task->getDescription()));
//        if (task->hasEvaluation()) {
//            ui->TW_TaskSelect->setItem(row, TASK_EVAL_RATING_COL, new QTableWidgetItem(task->getEvaluation()->getRatingString()));
//            ui->TW_TaskSelect->setItem(row, TASK_EVAL_COMMENT_COL, new QTableWidgetItem(task->getEvaluation()->getComment()));
//        } else {
//            ui->TW_TaskSelect->setItem(row, TASK_EVAL_RATING_COL, new QTableWidgetItem(Evaluation::ratingForEnum(RATING::NONE)));
//            ui->TW_TaskSelect->setItem(row, TASK_EVAL_COMMENT_COL, new QTableWidgetItem(QString("")));
//        }

//    }
}


void TaWindow::selectCourse(Course* course) {

}


void TaWindow::currentCourseComboIndexChanged() {

}

void TaWindow::recievedTaskListForTa(QString view, QList<Task *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedTaskListForTaResponse(QString,QList<Task*>)), this, SLOT(recievedTaskListForTa(QString,QList<Task*>)));
    if (view.compare(MANAGE_TASK_VIEW) == 0) {
        ui->TW_TaskSelect->setRowCount(0);

        taskMap.clear();
        foreach (Task* task, list) {
            qDebug() << "View: " << view << " Task name: " << task->getName() << " Task ID: " << task->getId();
            // Insert Task and Evaluation data into table
            int row = ui->TW_TaskSelect->rowCount();
            taskMap.insert(row, task);

            ui->TW_TaskSelect->insertRow(row);
            ui->TW_TaskSelect->setItem(row, TASK_NAME_COL, new QTableWidgetItem(task->getName()));
            ui->TW_TaskSelect->setItem(row, TASK_DESCRIPTION_COL, new QTableWidgetItem(task->getDescription()));
            if (task->hasEvaluation()) {
                ui->TW_TaskSelect->setItem(row, TASK_EVAL_RATING_COL, new QTableWidgetItem(task->getEvaluation()->getRatingString()));
                ui->TW_TaskSelect->setItem(row, TASK_EVAL_COMMENT_COL, new QTableWidgetItem(task->getEvaluation()->getComment()));
            } else {
                ui->TW_TaskSelect->setItem(row, TASK_EVAL_RATING_COL, new QTableWidgetItem(Evaluation::ratingForEnum(RATING::NONE)));
                ui->TW_TaskSelect->setItem(row, TASK_EVAL_COMMENT_COL, new QTableWidgetItem(QString("")));
            }

        }
    }
}
