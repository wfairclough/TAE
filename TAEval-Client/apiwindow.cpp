#include "apiwindow.h"
#include "ui_apiwindow.h"
#include "connectionclient.h"

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
    //Delete Task Style
    ui->dt_taTable->resizeColumnsToContents();
    ui->dt_taTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->dt_taTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->dt_taTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->dt_taskTable->resizeColumnsToContents();
    ui->dt_taskTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->dt_taskTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->dt_taTable->setStyleSheet("color:#222");
    ui->dt_taskTable->setStyleSheet("color:#222");
    ui->dt_execute->setStyleSheet("color: #222;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
}

//PUBLIC SLOTS//
void ApiWindow::recievedTaListForInstructor(QList<TeachingAssistant *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedTaListForInstructorResponse(QList<TeachingAssistant*>)), this, SLOT(recievedTaListForInstructor(QList<TeachingAssistant*>)));
    ui->taTable->setRowCount(0);
    foreach (TeachingAssistant* ta, list) {
        qDebug() << "TA Username: " << ta->getUsername();
        int row = ui->taTable->rowCount();
        ui->taTable->insertRow(row);
        ui->taTable->setItem(row, 0, new QTableWidgetItem(ta->getFirstName()));
        ui->taTable->setItem(row, 1, new QTableWidgetItem(ta->getLastName()));
        ui->taTable->setItem(row, 2, new QTableWidgetItem(ta->getUsername()));
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
    ic.getTaForInstructor(QString("claurendeau"));
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

ApiWindow::~ApiWindow()
{
    delete ui;
}
