#include "instructorwindow.h"
#include "ui_instructorwindow.h"
#include "instructorcontrol.h"
#include "tacontrol.h"
#include "connectionclient.h"
#include <QDebug>

InstructorWindow::InstructorWindow(Instructor* user, QWidget *parent) :
    instructor(user),
    QMainWindow(parent),
    ui(new Ui::InstructorWindow)
{
    ui->setupUi(this);

    connect(ui->courseComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(currentCourseComboIndexChanged(int)));
    connect(ui->taTable, SIGNAL(cellClicked(int,int)), this, SLOT(taCellClicked(int, int)));
    connect(ui->taskTable, SIGNAL(cellClicked(int,int)), this, SLOT(taskCellClicked(int, int)));
    connect(ui->editButton, SIGNAL(released()), this, SLOT(switchToEditView()));
    connect(ui->newButton, SIGNAL(released()), this, SLOT(switchToNewView()));
    connect(ui->newButton4, SIGNAL(released()), this, SLOT(switchToNewView()));
    connect(ui->cancelButton, SIGNAL(released()), this, SLOT(cancelEdit()));
    connect(ui->deleteButton, SIGNAL(released()), this, SLOT(deleteTask()));
    connect(ui->saveButton, SIGNAL(released()), this, SLOT(saveTask()));

    setWindowTitle("Instructor: " + user->getFullName());
    initInstructorView();

    ConnectionClient::getInstance().subscribe(this);

    InstructorControl ic;
    ic.getCoursesForInstructor(user->getUsername());

}
// Public Functions
void InstructorWindow::updateTaskListForTaAndCourse(QList<Task*> list) {
    taskMap.clear();
    ui->taskTable->setRowCount(0);
    int row = 0;

    foreach(Task* task, list) {
        row = ui->taskTable->rowCount();
        ui->taskTable->insertRow(row);
        ui->taskTable->setItem(row,TASK_COL_NAME, new QTableWidgetItem(task->getName()));
        if (task->hasEvaluation()) {
            ui->taskTable->setItem(row,TASK_COL_EVALUATED, new QTableWidgetItem("Evaluated"));
        } else {
            ui->taskTable->setItem(row,TASK_COL_EVALUATED, new QTableWidgetItem("No Evaluation"));
        }

        taskMap.insert(row++, task);
    }
}

void InstructorWindow::updateTaListForInstructor(QList<TeachingAssistant*> list) {
    taMap.clear();
    ui->taTable->setRowCount(0);
    int row = 0;

    foreach(TeachingAssistant* ta, list) {
        row = ui->taTable->rowCount();
        ui->taTable->insertRow(row);
        ui->taTable->setItem(row,TA_COL_NAME, new QTableWidgetItem(ta->getFirstName()));
        taMap.insert(row++, ta);
    }
}

void InstructorWindow::updateCourseListForInstructor(QList<Course*> list) {
    courseMap.clear();
    ui->courseComboBox->clear();

    int index = 0;
    foreach(Course* course, list) {
        courseMap.insert(index++, course);
        ui->courseComboBox->addItem(course->getFullCourseName());
    }
}

void InstructorWindow::updateAddTaskForTa(QList<Task*> list) {

}

void InstructorWindow::updateEvaluationListForTasks(QList<Evaluation*> list) {

}

// Public Slots
void InstructorWindow::currentCourseComboIndexChanged(int index) {
    selectCourse(courseMap.value(index));

}

void InstructorWindow::taCellClicked(int row, int col) {
    TaControl tc;
    tc.getTaskListForTaAndCourse(taMap.value(row), courseMap.value(ui->courseComboBox->currentIndex()));
    ui->rightWidget->setCurrentIndex(TASK_INFO_NEW_INDEX);
}

void InstructorWindow::taskCellClicked(int row, int col) {
    ui->rightWidget->setCurrentIndex(TASK_INFO_VIEW_INDEX);
    ui->name->setText(taskMap.value(row)->getName());
    ui->description->setText(taskMap.value(row)->getDescription());
    if (taskMap.value(row)->hasEvaluation()) {
        ui->rating->setText(taskMap.value(row)->getEvaluation()->getRatingString());
        ui->comment->setText(taskMap.value(row)->getEvaluation()->getComment());
    } else {
        ui->rating->setText(QString("None"));
        ui->comment->setText(QString("None"));
    }
}

void InstructorWindow::switchToEditView() {
    ui->rightWidget->setCurrentIndex(TASK_INFO_EDIT_INDEX);
    int row = ui->taskTable->currentRow();
    ui->editName->setText(taskMap.value(row)->getName());
    ui->editDescription->setText(taskMap.value(row)->getDescription());
    if (taskMap.value(row)->hasEvaluation()) {
        ui->editRating->setCurrentIndex(taskMap.value(row)->getEvaluation()->getRating());
        ui->editComment->setText(taskMap.value(row)->getEvaluation()->getComment());
    } else {
        ui->editRating->setCurrentIndex(0);
        ui->editComment->setText("");
    }
}

void InstructorWindow::switchToNewView() {
    ui->rightWidget->setCurrentIndex(TASK_INFO_EDIT_INDEX);
    int row = ui->taskTable->currentRow();
    ui->editName->setText(QString(""));
    ui->editDescription->setText(QString(""));
    ui->editRating->setCurrentIndex(0);
    ui->editComment->setText(QString(""));
}

void InstructorWindow::cancelEdit() {
    ui->rightWidget->setCurrentIndex(TASK_INFO_NEW_INDEX);
}

void InstructorWindow::deleteTask() {
    TaControl tc;
    Task *task = taskMap.value(ui->taskTable->currentRow());
    tc.deleteTask(task);
    TeachingAssistant *ta = taMap.value(ui->taTable->currentRow());
    Course *course = courseMap.value(ui->courseComboBox->currentIndex());
    tc.getTaskListForTaAndCourse(ta, course);
    ui->rightWidget->setCurrentIndex(TASK_INFO_HELP_INDEX);
}

void InstructorWindow::saveTask() {

}

// Private Functions
void InstructorWindow::initInstructorView() {
    ui->taTable->horizontalHeader()->setResizeMode(TA_COL_NAME, QHeaderView::Stretch);
    ui->taTable->horizontalHeader()->setResizeMode(TA_COL_RATING, QHeaderView::ResizeToContents);
    ui->taTable->setStyleSheet("color:#333");

    ui->taskTable->horizontalHeader()->setResizeMode(TASK_COL_NAME, QHeaderView::Stretch);
    ui->taskTable->horizontalHeader()->setResizeMode(TASK_COL_EVALUATED, QHeaderView::ResizeToContents);
    ui->taskTable->setStyleSheet("color:#333");

    ui->editRating->addItem("Select a Rating");
    ui->editRating->addItem("Poor - 1");
    ui->editRating->addItem("Fair - 2");
    ui->editRating->addItem("Good - 3");
    ui->editRating->addItem("Very Good - 4");
    ui->editRating->addItem("Excellent - 5");
}

void InstructorWindow::selectCourse(Course *course) {
    if (course != NULL) {
        InstructorControl ic;
        ic.getTaForInstructor(getCurrentInstructor()->getUsername());
    }
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}
