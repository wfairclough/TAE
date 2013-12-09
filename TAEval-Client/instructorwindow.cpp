#include "instructorwindow.h"
#include "ui_instructorwindow.h"
#include "instructorcontrol.h"
#include "tacontrol.h"
#include "connectionclient.h"
#include "loginwindow.h"
#include <QDebug>
#include <QMessageBox>

InstructorWindow::InstructorWindow(Instructor* user, QWidget *parent) :
    instructor(user),
    QMainWindow(parent),
    ui(new Ui::InstructorWindow)
{
    ui->setupUi(this);

    connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(logout()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->courseComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(currentCourseComboIndexChanged(int)));
    connect(ui->refreshButton, SIGNAL(released()), this, SLOT(refreshButtonReleased()));
    connect(ui->editRating, SIGNAL(currentIndexChanged(int)), this, SLOT(editRatingComboIndexChanged(int)));
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
    setCurrentTa(NULL);
    setCurrentTask(NULL);


}

void InstructorWindow::closeWindow() {
    ConnectionClient::getInstance().unsubscribe(this);
    close();
}

void InstructorWindow::connectionDisconnected() {
    logout();
}

void InstructorWindow::logout() {

    LoginWindow* loginWindow = new LoginWindow;
    loginWindow->show();

    closeWindow();
}

void InstructorWindow::quit() {
    QCoreApplication::exit();
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

void InstructorWindow::updateTaListForCourse(QList<TeachingAssistant*> list) {
    taMap.clear();
    ui->taTable->setRowCount(0);
    int row = 0;

    foreach(TeachingAssistant* ta, list) {
        row = ui->taTable->rowCount();
        ui->taTable->insertRow(row);
        ui->taTable->setItem(row,TA_COL_NAME, new QTableWidgetItem(ta->getFullName()));
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
    if (!courseMap.isEmpty()) {
        setCurrentCourse(courseMap.value(0));
    } else {
        setCurrentCourse(NULL);
        ui->refreshButton->setEnabled(false);
    }

    ui->taskTable->setRowCount(0); // clear the task list
    taskMap.clear();
}

void InstructorWindow::updateTask(Task* task) {
    setCurrentTask(task);
    TaControl tc;
    tc.getTaskListForTaAndCourse(getCurrentTa(), getCurrentCourse());
    selectTask(getCurrentTask());
}

// Private Slots
void InstructorWindow::currentCourseComboIndexChanged(int index) {
    selectCourse(courseMap.value(index));

}

void InstructorWindow::refreshButtonReleased() {
    selectCourse(getCurrentCourse());
}

void InstructorWindow::editRatingComboIndexChanged(int index) {
    if (index == 0) {
        ui->editComment->setEnabled(false);
    } else {
        ui->editComment->setEnabled(true);
    }
}

void InstructorWindow::taCellClicked(int row, int col) {
    selectTa(taMap.value(row));
}

void InstructorWindow::taskCellClicked(int row, int col) {
    selectTask(taskMap.value(row));
}

void InstructorWindow::switchToEditView() {
    if (getCurrentTask() == NULL) {
        setCurrentTask(new Task());
        ui->editRating->setVisible(false);
        ui->ratingLabel3->setVisible(false);
        ui->editComment->setVisible(false);
        ui->commentLabel3->setVisible(false);
    } else {
        ui->editRating->setVisible(true);
        ui->ratingLabel3->setVisible(true);
        ui->editComment->setVisible(true);
        ui->commentLabel3->setVisible(true);
    }
    ui->rightWidget->setCurrentIndex(TASK_INFO_EDIT_INDEX);
    ui->editName->setText(getCurrentTask()->getName());
    ui->editDescription->setText(getCurrentTask()->getDescription());
    if (getCurrentTask()->hasEvaluation()) {
        ui->editRating->setCurrentIndex(getCurrentTask()->getEvaluation()->getRating());
        ui->editComment->setText(getCurrentTask()->getEvaluation()->getComment());
    } else {
        ui->editRating->setCurrentIndex(0);
        ui->editComment->setText("");
    }
}

void InstructorWindow::switchToNewView() {
    setCurrentTask(NULL);
    switchToEditView();
}

void InstructorWindow::cancelEdit() {
    if (getCurrentTask() == NULL || getCurrentTask()->getId() < 0) {
        selectTa(getCurrentTa());
    } else {
        selectTask(getCurrentTask());
    }
}

void InstructorWindow::deleteTask() {
    TaControl tc;
    tc.deleteTask(getCurrentTask());
    tc.getTaskListForTaAndCourse(getCurrentTa(), getCurrentCourse());
    if (taskMap.isEmpty()) {
        ui->rightWidget->setCurrentIndex(TASK_INFO_HELP_INDEX);
        setCurrentTask(NULL);
    } else {
        selectTa(getCurrentTa());
    }
}

void InstructorWindow::saveTask() {
    TaControl tc;
    Task *task = getCurrentTask();
    Evaluation *eval = new Evaluation();

    if (task == NULL) {
        task = new Task;
    }
    task->setName(ui->editName->text());
    task->setDescription(ui->editDescription->toPlainText());
    if (ui->editRating->isVisible() && ui->editRating->currentIndex() != 0) {
        eval->setRating(ui->editRating->currentIndex());
        eval->setComment(ui->editComment->toPlainText());
        task->setEvaluation(eval);
    } else {
        task->setEvaluation(NULL);
    }
    setCurrentTask(task);
    tc.updateTaskAndEvaluation(task, getCurrentInstructor()->getUsername(), getCurrentTa()->getUsername());
}

// Private Functions
void InstructorWindow::initInstructorView() {
    ui->taTable->horizontalHeader()->setResizeMode(TA_COL_NAME, QHeaderView::Stretch);
    ui->taTable->horizontalHeader()->setResizeMode(TA_COL_RATING, QHeaderView::ResizeToContents);
    ui->taTable->setStyleSheet("color:#333");

    ui->taskTable->horizontalHeader()->setResizeMode(TASK_COL_NAME, QHeaderView::Stretch);
    ui->taskTable->horizontalHeader()->setResizeMode(TASK_COL_EVALUATED, QHeaderView::ResizeToContents);
    ui->taskTable->setStyleSheet("color:#333");

    setupEditRatingText(QString("No Evaluation"));
    ui->refreshButton->setIcon(QIcon("Resources/refresh.png"));
}

void InstructorWindow::setupEditRatingText(QString firstItem) {
    ui->editRating->clear();
    ui->editRating->addItem(firstItem);
    ui->editRating->addItem("Poor - 1");
    ui->editRating->addItem("Fair - 2");
    ui->editRating->addItem("Good - 3");
    ui->editRating->addItem("Very Good - 4");
    ui->editRating->addItem("Excellent - 5");
}

void InstructorWindow::selectCourse(Course *course) {
    if (course != NULL) {
        setCurrentCourse(course);
        InstructorControl ic;
        ic.getTaForCourse(getCurrentCourse());
    }
}

void InstructorWindow::selectTa(TeachingAssistant *ta) {
    if (ta != NULL) {
        TaControl tc;
        tc.getTaskListForTaAndCourse(ta, getCurrentCourse());
        ui->rightWidget->setCurrentIndex(TASK_INFO_NEW_INDEX);
        setCurrentTa(ta);
        setCurrentTask(NULL);
    }
}

void InstructorWindow::selectTask(Task* task) {
    ui->rightWidget->setCurrentIndex(TASK_INFO_VIEW_INDEX);
    ui->name->setText(task->getName());
    ui->description->setText(task->getDescription());
    if (task->hasEvaluation()) {
        ui->rating->setText(task->getEvaluation()->getRatingString());
        ui->comment->setText(task->getEvaluation()->getComment());
    } else {
        ui->rating->setText(QString("None"));
        ui->comment->setText(QString("None"));
    }
    setCurrentTask(task);
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}
