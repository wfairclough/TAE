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

    initManageTaskView();
    initViewCourseView();
    //set styles
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setStyleSheet("color: #eee;");
    ui->buttonWidget->setStyleSheet("background: #111;"
                                    "color: #bbb;");
    ui->manageTaskButton->setStyleSheet("background-color: #111;");
    ui->viewCourseButton->setStyleSheet("background-color: #111;");
}

void ApiWindow::initManageTaskView() {
    // Delete Task View
    connect(ui->manageTaskButton, SIGNAL(released()), this, SLOT(handleManageTask()));
    connect(ui->mt_instructorTable, SIGNAL(cellClicked(int,int)), this, SLOT(mtinstructorCellClicked(int, int)));
    connect(ui->mt_taTable, SIGNAL(cellClicked(int,int)), this, SLOT(mttaCellClicked(int, int)));
    connect(ui->mt_taskTable, SIGNAL(cellClicked(int,int)), this, SLOT(mttaskCellClicked(int, int)));
    connect(ui->mt_delete, SIGNAL(released()), this, SLOT(mtdeleteClicked()));
    connect(ui->mt_taskTable, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(mtcellItemChanged(QTableWidgetItem*)));
    connect(ui->mt_taskTable, SIGNAL(cellChanged(int,int)), this, SLOT(mttaskTableCellChanged(int, int)) );

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
    ui->mt_taTable->setStyleSheet("color:#333");
    ui->mt_taskTable->setStyleSheet("color:#333");
    ui->mt_instructorTable->setStyleSheet("color: #333");
    ui->mt_update->setEnabled(true);
    ui->mt_update->setStyleSheet("color: #333;"
                                  "background-color: #eee;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
    disableButton(ui->mt_delete);
}

void ApiWindow::initViewCourseView() {
    // View Course View
    connect(ui->viewCourseButton, SIGNAL(released()), this, SLOT(handleViewCourse()));
    connect(ui->vc_instructorComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(vcinstructorComboBoxChanged(QString)));

    ui->vc_courseTable->resizeColumnsToContents();
    ui->vc_courseTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->vc_courseTable->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->vc_courseTable->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->vc_courseTable->setStyleSheet("color: #333;"
                                  "font: Helvetica Neue;"
                                  "background-color: #fafafa");
    ui->vc_courseTable->horizontalHeader()->setStyleSheet("font-size: 12pt");
    ui->vc_courseTable->verticalHeader()->setStyleSheet("font-size: 12pt");
    ui->vc_instructorComboBox->setStyleSheet("color: #333;"
                                      "font: Helvetica Neue;"
                                       "font-size: 14pt;"
                                       "font-weight: bold;");
}

//PUBLIC SLOTS//
void ApiWindow::recievedTaListForInstructor(QString view, QList<TeachingAssistant *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedTaListForInstructorResponse(QString, QList<TeachingAssistant*>)), this, SLOT(recievedTaListForInstructor(QString, QList<TeachingAssistant*>)));
    if(view.compare(MANAGE_TASK_VIEW) == 0) {
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
    if (view.compare(VIEW_COURSE_VIEW) == 0) {
        ui->vc_courseTable->setRowCount(0);
        foreach (Course* course, list) {
            qDebug() << "Course Name:" << course->getName() << "in View: " << view;
            int row = ui->vc_courseTable->rowCount();
            ui->vc_courseTable->insertRow(row);
            ui->vc_courseTable->setItem(row, 0, new QTableWidgetItem(course->getName()));
            ui->vc_courseTable->setItem(row, 1, new QTableWidgetItem(course->getSemesterTypeString()));
            ui->vc_courseTable->setItem(row, 2, new QTableWidgetItem(QString::number(course->getYear())));
        }
    }
}

void ApiWindow::recievedInstructorList(QString view, QList<Instructor*> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedInstructorListResponse(QString, QList<Instructor*>)), this, SLOT(recievedInstructorList(QString, QList<Instructor*>)));
    if (view.compare(MANAGE_TASK_VIEW) == 0) {
        ui->mt_instructorTable->setRowCount(0);
        foreach (Instructor* prof, list) {
            qDebug() << "Instructor Username: " << prof->getUsername();
            int row = ui->mt_instructorTable->rowCount();
            ui->mt_instructorTable->insertRow(row);
            ui->mt_instructorTable->setItem(row, 0, new QTableWidgetItem(prof->getFirstName()));
            ui->mt_instructorTable->setItem(row, 1, new QTableWidgetItem(prof->getLastName()));
            ui->mt_instructorTable->setItem(row, 2, new QTableWidgetItem(prof->getUsername()));
        }
    } else if (view.compare(VIEW_COURSE_VIEW) == 0) {
        QStringList profList;
        foreach (Instructor* prof, list) {
            profList.append(prof->getUsername() + " - " + prof->getFirstName() + " " + prof->getLastName());
        }
        ui->vc_instructorComboBox->clear();
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
    if (view.compare(MANAGE_TASK_VIEW) == 0) {
        qDebug() << "View 3";
        ui->mt_taskTable->setRowCount(0);
        foreach (Task* task, list) {
            qDebug() << "View: " << view << " Task name: " << task->getName();
            int row = ui->mt_taskTable->rowCount();
            taskMap.insert(row, task);

            ui->mt_taskTable->insertRow(row);
            ui->mt_taskTable->setItem(row, TASK_NAME_COL, new QTableWidgetItem(task->getName()));
            ui->mt_taskTable->setItem(row, TASK_DESCRIPTION_COL, new QTableWidgetItem(task->getDescription()));
        }
    }

}

void ApiWindow::mttaskTableCellChanged(int row, int column) {
    Task* task = taskMap.value(row);

    QTableWidgetItem* item = ui->mt_taskTable->item(row, column);
    if (column == TASK_NAME_COL) {
        task->setName(item->text());
    } else if (column == TASK_DESCRIPTION_COL) {
        task->setDescription(item->text());
    }

    TaControl tc(this);
    tc.updateTask(task);
}

void ApiWindow::recievedDeleteTaskForTa(QString view, QList<Task *> list) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedDeleteTaskForTaResponse(QString,QList<Task*>)), this, SLOT(recievedDeleteTaskForTa(QString,QList<Task*>)));
    if (view.compare(MANAGE_TASK_VIEW) == 0) {
        ui->mt_taskTable->removeRow(ui->mt_taskTable->currentRow());
    }
}


//PRIVATE SLOTS//
/**
 * Description: Handles the released SIGNAL from deleteTaskButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleManageTask() {
    ui->stackedWidget->setCurrentIndex(1);
    updateViewStyles(MANAGE_TASK_VIEW);
    InstructorControl ic(this);
    ic.getInstructors(QString(MANAGE_TASK_VIEW));
}

/**
 * Description: Handles the released SIGNAL from viewCourseButton
 * Paramters: None
 * Returns: None
 */
void ApiWindow::handleViewCourse() {
    ui->stackedWidget->setCurrentIndex(2);
    updateViewStyles(VIEW_COURSE_VIEW);
    InstructorControl ic(this);
    ic.getInstructors(VIEW_COURSE_VIEW);
}

// Manage Task Slots
/**
 * Description: handles everytime mt_instructorTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::mtinstructorCellClicked(int currentRow, int currentCol){
    InstructorControl ic(this);
    ic.getTaForInstructor(QString(MANAGE_TASK_VIEW), ui->mt_instructorTable->item(currentRow,2)->text());
    ui->mt_taskTable->setRowCount(0);
    disableButton(ui->mt_delete);
    disableButton(ui->mt_update);
}

/**
 * Description: handles everytime mt_taTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::mttaCellClicked(int currentRow, int currentCol){
    TaControl tc(this);
    tc.getTaskListForTa(QString(MANAGE_TASK_VIEW),ui->mt_taTable->item(currentRow,2)->text());
    disableButton(ui->mt_delete);
    disableButton(ui->mt_update);
}

/**
 * Description: handles everytime mt_taskTable's cell's are clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::mttaskCellClicked(int currentRow, int currentCol){
    enableButton(ui->mt_delete);
}

/**
 * Description: handles everytime mt_deleteButton is clicked
 * Paramters: the row and column that was clikced
 * Returns: None
 */
void ApiWindow::mtdeleteClicked() {
    TaControl tc(this);
    tc.deleteTaskForTA(QString(MANAGE_TASK_VIEW), ui->mt_taskTable->item(ui->mt_taskTable->currentRow(),0)->text(), ui->mt_taTable->item(ui->mt_taTable->currentRow(),2)->text());
    disableButton(ui->mt_delete);
    disableButton(ui->mt_update);
}

/**
 * Description: handles everytime mt_taskTable item is edited
 * Paramters: the item that was edited
 * Returns: None
 */
void ApiWindow::mtcellItemChanged(QTableWidgetItem *item) {
    enableButton(ui->mt_update);
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
    ic.getCoursesForInstructor(VIEW_COURSE_VIEW, profUsername);
}

//PRIVATE FUNCTIONS

void ApiWindow::enableButton(QPushButton *&button) {
    button->setEnabled(true);
    button->setStyleSheet("color: #333;"
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
void ApiWindow::disableButton(QPushButton *&button) {
    button->setEnabled(false);
    button->setStyleSheet("color: #ccc;"
                                  "background-color: #999;"
                                  "font: Hevetica Neue;"
                                  "font-size: 14pt;"
                                  "font-style: bold;");
}

/**
 * Description: set manageTaskButton's style to match its state
 * Paramters: None
 * Returns: None
 */
void ApiWindow::mangeTaskSelectedStyle() {
    ui->manageTaskButton->setStyleSheet("background-color: #333;"
                                        "color: #fff;");
    disableButton(ui->mt_delete);
    disableButton(ui->mt_update);
}

/**
 * Description: set manageTaskButton's style to match its state
 * Paramters: None
 * Returns: None
 */
void ApiWindow::manageTaskDeselectedStyle() {
    ui->manageTaskButton->setStyleSheet("background-color: #111;"
                                        "color: #bbb;");
}

/**
 * Description: set viewCourseButton's style to match its state
 * Paramters: None
 * Returns: None
 */
void ApiWindow::viewCourseSelectedStyle() {
    ui->viewCourseButton->setStyleSheet("background-color: #333;"
                                        "color: #fff;");
}

/**
 * Description: set viewCourseButton's style to match its state
 * Paramters: None
 * Returns: None
 */
void ApiWindow::viewCourseDeSelectedStyle() {
    ui->viewCourseButton->setStyleSheet("background-color: #111;"
                                        "color: #bbb;");
}

/**
 * Description: updates the style of all buttons to match current state
 * Paramters: None
 * Returns: None
 */
void ApiWindow::updateViewStyles(QString selectedView) {
    if (selectedView.compare(MANAGE_TASK_VIEW) == 0) {
        mangeTaskSelectedStyle();
        viewCourseDeSelectedStyle();
    } else if (selectedView.compare(VIEW_COURSE_VIEW) == 0) {
        viewCourseSelectedStyle();
        manageTaskDeselectedStyle();
    }
}

ApiWindow::~ApiWindow()
{
    delete ui;
}
