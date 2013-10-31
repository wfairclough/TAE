#include "apiwindow.h"
#include "ui_apiwindow.h"
#include "connectionclient.h"
#include "tacontrol.h"

ApiWindow::ApiWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApiWindow)
{
    ui->setupUi(this);
    connect(ui->newTaskButton, SIGNAL(released()), this, SLOT(handleNewTask()));
    connect(ui->editTaskButton, SIGNAL(released()), this, SLOT(handleEditTask()));
    connect(ui->deleteTaskButton, SIGNAL(released()), this, SLOT(handleDeleteTask()));
    connect(ui->assignTaskButton, SIGNAL(released()), this, SLOT(handleAssignTask()));
    connect(ui->evaluateTaskButton, SIGNAL(released()), this, SLOT(handleEvaluateTask()));
    connect(ui->viewTaButton, SIGNAL(released()), this, SLOT(handleViewTa()));
    connect(ui->viewCourseButton, SIGNAL(released()), this, SLOT(handleViewCourse()));
    connect(ui->viewTaskButton, SIGNAL(released()), this, SLOT(handleViewTask()));

    ConnectionClient::getInstance().connectToServer();

    //set styles
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setStyleSheet("color: #eee;");
    //View Teaching Assistant Style
    ui->taTable->resizeColumnsToContents();
    ui->taTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->taTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->taTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->taTable->setStyleSheet("color: #222;"
                               "font: Helvetica Neue;"
                               "background-color: #fafafa");
    ui->taTable->horizontalHeader()->setStyleSheet("font-size: 12pt");
    ui->taTable->verticalHeader()->setStyleSheet("font-size: 12pt");

    //View Courses Styles                                               ////////////////////////////////////////ADDED //////////////////////////////////////
    ui->courseTable->resizeColumnsToContents();
    ui->courseTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->courseTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->courseTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->courseTable->setStyleSheet("color: #222;"
                                  "font: Helvetica Neue;"
                                  "background-color: #fafafa");
    ui->courseTable->horizontalHeader()->setStyleSheet("font-size: 12pt");
    ui->courseTable->verticalHeader()->setStyleSheet("font-size: 12pt");

    //Delete Task Style
    ui->dt_taTable->resizeColumnsToContents();
    ui->dt_taTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->dt_taTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->dt_taTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->dt_instructorTable->resizeColumnsToContents();
    ui->dt_instructorTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->dt_instructorTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->dt_instructorTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->dt_taskTable->resizeColumnsToContents();
    ui->dt_taskTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->dt_taskTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->dt_taTable->setStyleSheet("color:#222");
    ui->dt_taskTable->setStyleSheet("color:#222");
    ui->dt_instructorTable->setStyleSheet("color: #222");
    ui->dt_execute->setStyleSheet("color: #222;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
}

//PUBLIC SLOTS//
void ApiWindow::recievedTaListForInstructor(QString view, QList<TeachingAssistant *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedTaListForInstructorResponse(QString, QList<TeachingAssistant*>)), this, SLOT(recievedTaListForInstructor(QString, QList<TeachingAssistant*>)));
    if (view.compare("6") == 0) {
        ui->taTable->setRowCount(0);
        foreach (TeachingAssistant* ta, list) {
            qDebug() << "TA Username: " << ta->getUsername() << " in View: " << view;
            int row = ui->taTable->rowCount();
            ui->taTable->insertRow(row);
            ui->taTable->setItem(row, 0, new QTableWidgetItem(ta->getFirstName()));
            ui->taTable->setItem(row, 1, new QTableWidgetItem(ta->getLastName()));
            ui->taTable->setItem(row, 2, new QTableWidgetItem(ta->getUsername()));
        }
    } else if(view.compare("3") == 0) {
        ui->dt_taTable->setRowCount(0);
        foreach (TeachingAssistant* ta, list) {
            qDebug() << "TA Username: " << ta->getUsername() << " in View: " << view;
            int row = ui->dt_taTable->rowCount();
            ui->dt_taTable->insertRow(row);
            ui->dt_taTable->setItem(row, 0, new QTableWidgetItem(ta->getFirstName()));
            ui->dt_taTable->setItem(row, 1, new QTableWidgetItem(ta->getLastName()));
            ui->dt_taTable->setItem(row, 2, new QTableWidgetItem(ta->getUsername()));
        }
    }
}
void ApiWindow::recievedCourseListForInstructor(QString view, QList<Course *> list) { ////////////////////////////////////////ADDED //////////////////////////////////////
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedCourseListForInstructorResponse(QString,QList<Course*>)), this, SLOT(recievedCourseListForInstructor(QString,QList<Course*>)));
    if (view.compare("7") == 0) {
        ui->courseTable->setRowCount(0);
        foreach (Course* course, list) {
            qDebug() << "Course Name:" << course->getName() << "in View: " << view;
            int row = ui->courseTable->rowCount();
            ui->courseTable->insertRow(row);
            ui->courseTable->setItem(row, 0, new QTableWidgetItem(course->getName()));
            ui->courseTable->setItem(row, 1, new QTableWidgetItem(course->getSemesterType()));
            ui->courseTable->setItem(row, 2, new QTableWidgetItem(course->getYear()));
        }
    }
}

void ApiWindow::recievedInstructorList(QString view, QList<Instructor*> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedInstructorListResponse(QList<Instructor*>)), this, SLOT(recievedInstructorList(QList<Instructor*>)));
    if (view.compare("3") == 0) {
        ui->dt_instructorTable->setRowCount(0);
        foreach (Instructor* prof, list) {
            qDebug() << "Instructor Username: " << prof->getUsername();
            int row = ui->dt_instructorTable->rowCount();
            ui->dt_instructorTable->insertRow(row);
            ui->dt_instructorTable->setItem(row, 0, new QTableWidgetItem(prof->getFirstName()));
            ui->dt_instructorTable->setItem(row, 1, new QTableWidgetItem(prof->getLastName()));
            ui->dt_instructorTable->setItem(row, 2, new QTableWidgetItem(prof->getUsername()));
        }
    }
}

void ApiWindow::recievedTaList(QString view, QList<TeachingAssistant *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedTaListResponse(QString, QList<TeachingAssistant*>)), this, SLOT(recievedTaList(QString, QList<TeachingAssistant*>)));
    if (view.compare("0") == 0) {

    }
}

void ApiWindow::recievedTaskListForTa(QString view, QList<Task *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedTaskListForTaResponse(QString,QList<Task*>)), this, SLOT(recievedTaskListForTa(QString,QList<Task*>)));
    if (view.compare("3") == 0) {
        qDebug() << "View 3";
        ui->dt_taskTable->setRowCount(0);
        foreach (Task* task, list) {
            qDebug() << "View: " << view << " Task name: " << task->getName();
            int row = ui->dt_taskTable->rowCount();
            ui->dt_taskTable->insertRow(row);
            ui->dt_taskTable->setItem(row, 0, new QTableWidgetItem(task->getName()));
            ui->dt_taskTable->setItem(row, 1, new QTableWidgetItem(task->getDescription()));
        }
    }
}


//PRIVATE SLOTS//
/**
 * Description: Handles the released SIGNAL from newTaskButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleNewTask() {
    qDebug("create task");
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * Description: Handles the released SIGNAL from editTaskButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleEditTask() {
    qDebug("edit task");
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * Description: Handles the released SIGNAL from deleteTaskButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleDeleteTask() {
    qDebug("delete task");
    ui->stackedWidget->setCurrentIndex(3);
    InstructorControl ic(this);
    TaControl tc(this);
    ic.getInstructors(QString("3"));
    ic.getTaForInstructor(QString("3"), QString("claurendeau"));
    tc.getTaskListForTa(QString("3"), QString("shurtado"));
    tc.getTas(QString("0"));
    ui->dt_instructorTable->selectRow(0);
}

/**
 * Description: Handles the released SIGNAL from assignTaskButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleAssignTask() {
    qDebug("assign task");
    ui->stackedWidget->setCurrentIndex(4);
}

/**
 * Description: Handles the released SIGNAL from evaluateTaskButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleEvaluateTask() {
    qDebug("evaluate task");
    ui->stackedWidget->setCurrentIndex(5);
}

/**
 * Description: Handles the released SIGNAL from viewTaButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleViewTa() {
    qDebug("view TA");
    ui->stackedWidget->setCurrentIndex(6);
    InstructorControl ic(this);
    ic.getTaForInstructor(QString("6"), QString("claurendeau"));
}

/**
 * Description: Handles the released SIGNAL from viewCourseButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleViewCourse() { ////////////////////////////////////Added ////////////////////////////////////
    qDebug("view course");
    ui->stackedWidget->setCurrentIndex(7);
    InstructorControl ic(this);
    ic.getCoursesForInstructor(QString("7"), QString("claurendeau"));
}

/**
 * Description: Handles the released SIGNAL from viewTaskButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleViewTask() {
    qDebug("view task");
    ui->stackedWidget->setCurrentIndex(8);
}

ApiWindow::~ApiWindow()
{
    delete ui;
}
