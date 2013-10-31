#include "apiwindow.h"
#include "ui_apiwindow.h"
#include "connectionclient.h"
#include "tacontrol.h"

ApiWindow::ApiWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApiWindow)
{
    ui->setupUi(this);

    ConnectionClient::getInstance().connectToServer();


    initCreateTaskView();
    initEditTaskView();
    initDeleteTaskView();
    initAssignTaskView();
    initEvaluateTask();
    initViewTaView();
    initViewCourseView();
    initViewTaskView();

}

void ApiWindow::initCreateTaskView() {
    // New Task View
    connect(ui->newTaskButton, SIGNAL(released()), this, SLOT(handleNewTask()));
}

void ApiWindow::initEditTaskView() {
    // Edit Task View
    connect(ui->editTaskButton, SIGNAL(released()), this, SLOT(handleEditTask()));
}

void ApiWindow::initDeleteTaskView() {
    // Delete Task View
    connect(ui->deleteTaskButton, SIGNAL(released()), this, SLOT(handleDeleteTask()));
    connect(ui->dt_instructorTable, SIGNAL(cellClicked(int,int)), this, SLOT(dtinstructorCellClicked(int, int)));
    connect(ui->dt_taTable, SIGNAL(cellClicked(int,int)), this, SLOT(dttaCellClicked(int, int)));
    connect(ui->dt_taskTable, SIGNAL(cellClicked(int,int)), this, SLOT(dttaskCellClicked(int, int)));
    connect(ui->dt_execute, SIGNAL(released()), this, SLOT(dtexecuteClicked()));


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
    disableExecuteButton();
}

void ApiWindow::initAssignTaskView() {
    // Assign Task View
    connect(ui->assignTaskButton, SIGNAL(released()), this, SLOT(handleAssignTask()));
}

void ApiWindow::initEvaluateTask() {
    // Evaluate TAsk View
    connect(ui->evaluateTaskButton, SIGNAL(released()), this, SLOT(handleEvaluateTask()));
}

void ApiWindow::initViewTaView() {
    // View Teaching Assistants View
    connect(ui->viewTaButton, SIGNAL(released()), this, SLOT(handleViewTa()));
}

void ApiWindow::initViewCourseView() {
    // View Course View
    connect(ui->viewCourseButton, SIGNAL(released()), this, SLOT(handleViewCourse()));
}

void ApiWindow::initViewTaskView() {
    // View Tasks View
    connect(ui->viewTaskButton, SIGNAL(released()), this, SLOT(handleViewTask()));
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

void ApiWindow::recievedInstructorList(QString view, QList<Instructor*> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedInstructorListResponse(QString, QList<Instructor*>)), this, SLOT(recievedInstructorList(QString, QList<Instructor*>)));
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
    } else if (view.compare("1") == 0) {
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

void ApiWindow::recievedDeleteTaskForTa(QString view, QList<Task *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedDeleteTaskForTaResponse(QString,QList<Task*>)), this, SLOT(recievedDeleteTaskForTa(QString,QList<Task*>)));
    if (view.compare("3") == 0) {
        ui->dt_taskTable->removeRow(ui->dt_taskTable->currentRow());
    }
}

void ApiWindow::recievedAddTaskForTa(QString view, QList<Task*> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedAddTaskForTaResponse(QString,QList<Task*>)), this, SLOT(recievedAddTaskForTa(QString,QList<Task*>)));
    if (view.compare("1") == 0) {
        // Update View 1 with new list of Tasks
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

    TaControl taControl(this);

    taControl.addTaskForTa("1", "ederavi", "Mark Database Schema", "Make sure that all students DB schemas run with no errors. Follow Marking Scheme.");

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
    ic.getInstructors(QString("3"));
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
void ApiWindow::handleViewCourse() {
    qDebug("view course");
    ui->stackedWidget->setCurrentIndex(7);
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

// Delete Task Slots
/**
 * Description: handles everytime dt_instructorTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::dtinstructorCellClicked(int currentRow, int currentCol){
    InstructorControl ic(this);
    ic.getTaForInstructor(QString("3"),ui->dt_instructorTable->item(currentRow,2)->text());
    ui->dt_taskTable->setRowCount(0);
    disableExecuteButton();
}

/**
 * Description: handles everytime dt_taTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::dttaCellClicked(int currentRow, int currentCol){
    TaControl tc(this);
    tc.getTaskListForTa(QString("3"),ui->dt_taTable->item(currentRow,2)->text());
    disableExecuteButton();
}

/**
 * Description: handles everytime dt_taskTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::dttaskCellClicked(int currentRow, int currentCol){
    enableExecuteButton();
}

/**
 * Description: handles everytime dt_executeButton is clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::dtexecuteClicked() {
    TaControl tc(this);
    tc.deleteTaskForTA(QString("3"), ui->dt_taskTable->item(ui->dt_taskTable->currentRow(),0)->text(), ui->dt_taTable->item(ui->dt_taTable->currentRow(),2)->text());
    disableExecuteButton();
}

//PRIVATE FUNCTIONS
/**
 * Description: Enables the Execute Button and changes its style to match
 * Paramters: None
 * Returns: None
 */
void ApiWindow::enableExecuteButton() {
    ui->dt_execute->setEnabled(true);
    ui->dt_execute->setStyleSheet("color: #222;"
                                  "background-color: #eee;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
}

/**
 * Description: Disables the Execute Button and changes its style to match
 * Paramters: None
 * Returns: None
 */
void ApiWindow::disableExecuteButton() {
    ui->dt_execute->setEnabled(false);
    ui->dt_execute->setStyleSheet("color: #ccc;"
                                  "background-color: #999;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
}
ApiWindow::~ApiWindow()
{
    delete ui;
}
