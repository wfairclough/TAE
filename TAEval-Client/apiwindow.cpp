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
    connect(ui->mt_instructorTable, SIGNAL(cellClicked(int,int)), this, SLOT(mtinstructorCellClicked(int, int)));
    connect(ui->mt_taTable, SIGNAL(cellClicked(int,int)), this, SLOT(mttaCellClicked(int, int)));
    connect(ui->mt_taskTable, SIGNAL(cellClicked(int,int)), this, SLOT(mttaskCellClicked(int, int)));
    connect(ui->mt_delete, SIGNAL(released()), this, SLOT(mtdeleteClicked()));
    connect(ui->mt_taskTable, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(mtcellItemChanged(QTableWidgetItem*)));
    connect(ui->assignTaskButton, SIGNAL(released()), this, SLOT(handleAssignTask()));
    connect(ui->evaluateTaskButton, SIGNAL(released()), this, SLOT(handleEvaluateTask()));
    connect(ui->viewTaButton, SIGNAL(released()), this, SLOT(handleViewTa()));
    connect(ui->viewCourseButton, SIGNAL(released()), this, SLOT(handleViewCourse()));
    connect(ui->viewTaskButton, SIGNAL(released()), this, SLOT(handleViewTask()));
    connect(ui->vc_instructorComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(vcinstructorComboBoxChanged(QString)));


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

    //View Courses Styles
    ui->vc_courseTable->resizeColumnsToContents();
    ui->vc_courseTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->vc_courseTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->vc_courseTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->vc_courseTable->setStyleSheet("color: #222;"
                                  "font: Helvetica Neue;"
                                  "background-color: #fafafa");
    ui->vc_courseTable->horizontalHeader()->setStyleSheet("font-size: 12pt");
    ui->vc_courseTable->verticalHeader()->setStyleSheet("font-size: 12pt");
    ui->vc_instructorComboBox->setStyleSheet("color: #222;"
                                      "font: Helvetica Neue;"
                                       "font-size: 14pt;"
                                       "font-weight: bold;");

    //Delete Task Style
    ui->mt_taTable->resizeColumnsToContents();
    ui->mt_taTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->mt_taTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->mt_taTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->mt_instructorTable->resizeColumnsToContents();
    ui->mt_instructorTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->mt_instructorTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->mt_instructorTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->mt_taskTable->resizeColumnsToContents();
    ui->mt_taskTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->mt_taskTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->mt_taTable->setStyleSheet("color:#222");
    ui->mt_taskTable->setStyleSheet("color:#222");
    ui->mt_instructorTable->setStyleSheet("color: #222");
    ui->mt_update->setEnabled(true);
    ui->mt_update->setStyleSheet("color: #222;"
                                  "background-color: #eee;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
    disableDeleteButton();
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
        ui->mt_taTable->setRowCount(0);
        foreach (TeachingAssistant* ta, list) {
            qDebug() << "TA Username: " << ta->getUsername() << " in View: " << view;
            int row = ui->mt_taTable->rowCount();
            ui->mt_taTable->insertRow(row);
            ui->mt_taTable->setItem(row, 0, new QTableWidgetItem(ta->getFirstName()));
            ui->mt_taTable->setItem(row, 1, new QTableWidgetItem(ta->getLastName()));
            ui->mt_taTable->setItem(row, 2, new QTableWidgetItem(ta->getUsername()));
        }
    }
}
void ApiWindow::recievedCourseListForInstructor(QString view, QList<Course *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedCourseListForInstructorResponse(QString,QList<Course*>)), this, SLOT(recievedCourseListForInstructor(QString,QList<Course*>)));
    if (view.compare("7") == 0) {
        ui->vc_courseTable->setRowCount(0);
        foreach (Course* course, list) {
            qDebug() << "Course Name:" << course->getName() << "in View: " << view;
            int row = ui->vc_courseTable->rowCount();
            ui->vc_courseTable->insertRow(row);
            ui->vc_courseTable->setItem(row, 0, new QTableWidgetItem(course->getName()));
            ui->vc_courseTable->setItem(row, 1, new QTableWidgetItem(course->getSemesterTypeString()));
            ui->vc_courseTable->setItem(row, 2, new QTableWidgetItem(course->getYear()));
        }
    }
}

void ApiWindow::recievedInstructorList(QString view, QList<Instructor*> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedInstructorListResponse(QString, QList<Instructor*>)), this, SLOT(recievedInstructorList(QString, QList<Instructor*>)));
    if (view.compare("3") == 0) {
        ui->mt_instructorTable->setRowCount(0);
        foreach (Instructor* prof, list) {
            qDebug() << "Instructor Username: " << prof->getUsername();
            int row = ui->mt_instructorTable->rowCount();
            ui->mt_instructorTable->insertRow(row);
            ui->mt_instructorTable->setItem(row, 0, new QTableWidgetItem(prof->getFirstName()));
            ui->mt_instructorTable->setItem(row, 1, new QTableWidgetItem(prof->getLastName()));
            ui->mt_instructorTable->setItem(row, 2, new QTableWidgetItem(prof->getUsername()));
        }
    } else if (view.compare("7") == 0) {
        QStringList profList;
        foreach (Instructor* prof, list) {
            profList.append(prof->getUsername() + " - " + prof->getFirstName() + " " + prof->getLastName());
        }
        ui->vc_instructorComboBox->addItems(profList);
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
        ui->mt_taskTable->setRowCount(0);
        foreach (Task* task, list) {
            qDebug() << "View: " << view << " Task name: " << task->getName();
            int row = ui->mt_taskTable->rowCount();
            ui->mt_taskTable->insertRow(row);
            ui->mt_taskTable->setItem(row, 0, new QTableWidgetItem(task->getName()));
            ui->mt_taskTable->setItem(row, 1, new QTableWidgetItem(task->getDescription()));
        }
    }
}

void ApiWindow::recievedDeleteTaskForTa(QString view, QList<Task *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedDeleteTaskForTaResponse(QString,QList<Task*>)), this, SLOT(recievedDeleteTaskForTa(QString,QList<Task*>)));
    if (view.compare("3") == 0) {
        ui->mt_taskTable->removeRow(ui->mt_taskTable->currentRow());
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
    // TESTING COURSE METHODS
    Course* c = new Course();
    c->setName("C!");
    c->setSemesterType(Semester::WINTER);
    c->setYear(2015);
    qDebug() << c->getName() << "|" << c->getSemesterTypeString() << "|" << c->getYear();
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
    InstructorControl ic(this);
    ic.getInstructors("7");
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
 * Description: handles everytime mt_instructorTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::mtinstructorCellClicked(int currentRow, int currentCol){
    InstructorControl ic(this);
    ic.getTaForInstructor(QString("3"),ui->mt_instructorTable->item(currentRow,2)->text());
    ui->mt_taskTable->setRowCount(0);
    disableDeleteButton();
}

/**
 * Description: handles everytime mt_taTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::mttaCellClicked(int currentRow, int currentCol){
    TaControl tc(this);
    tc.getTaskListForTa(QString("3"),ui->mt_taTable->item(currentRow,2)->text());
    disableDeleteButton();
}

/**
 * Description: handles everytime mt_taskTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::mttaskCellClicked(int currentRow, int currentCol){
    enableDeleteButton();
}

/**
 * Description: handles everytime mt_deleteButton is clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::mtdeleteClicked() {
    TaControl tc(this);
    tc.deleteTaskForTA(QString("3"), ui->mt_taskTable->item(ui->mt_taskTable->currentRow(),0)->text(), ui->mt_taTable->item(ui->mt_taTable->currentRow(),2)->text());
    disableDeleteButton();
}

/**
 * Description: handles everytime mt_taskTable item is edited
 * Paramters: the item that was edited
 * Returns: None
 */
void ApiWindow::mtcellItemChanged(QTableWidgetItem *item) {
    qDebug() << item->text();
}

//PRIVATE FUNCTIONS
/**
 * Description: Enables the Delete Button and changes its style to match
 * Paramters: None
 * Returns: None
 */
void ApiWindow::enableDeleteButton() {
    ui->mt_delete->setEnabled(true);
    ui->mt_delete->setStyleSheet("color: #222;"
                                  "background-color: #eee;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
}

/**
 * Description: Disables the Delete Button and changes its style to match
 * Paramters: None
 * Returns: None
 */
void ApiWindow::disableDeleteButton() {
    ui->mt_delete->setEnabled(false);
    ui->mt_delete->setStyleSheet("color: #ccc;"
                                  "background-color: #999;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
}

// View Course Slots
/**
 * Description: loads vc_courseTable with the Instructor selected in vc_comboBox's Courses
 * Paramters: the QString from the comboBox that is currently selected
 * Returns: None
 */
void ApiWindow::vcinstructorComboBoxChanged(QString profInfo) {
    InstructorControl ic(this);
    QString profUsername = QString(profInfo.split(' ').at(0));
    ic.getCoursesForInstructor("7", profUsername);
}

ApiWindow::~ApiWindow()
{
    delete ui;
}
