#include "tawindow.h"
#include "ui_tawindow.h"
#include "connectionclient.h"
#include "tacontrol.h"
#include "loginwindow.h"


TaWindow::TaWindow(TeachingAssistant* user, QWidget *parent) :
    teachingAssistant(user),
    QMainWindow(parent),
    ui(new Ui::TaWindow)
{
    ui->setupUi(this);

    connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(logout()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->courseComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(currentCourseComboIndexChanged(int)));
    connect(ui->refreshButton, SIGNAL(released()), this, SLOT(refreshButtonReleased()));
    connect(ui->taskTable, SIGNAL(cellClicked(int,int)), this, SLOT(taskCellClicked(int, int)));

    initManageTaskView();
    setWindowTitle("Teaching Assistant: " + user->getFullName());

    ConnectionClient::getInstance().subscribe(this);

    TaControl tc;
    tc.getCoursesForTeachingAssistant(getCurrentTa());

    QAction* whatsThisAction = QWhatsThis::createAction(this);

    ui->menuHelp->addAction(whatsThisAction);
}

/**
 * Description: Sets the default styling when the TA Window is loaded
 * Paramters: None
 * Returns: Void
 */
void TaWindow::initManageTaskView(){
    ui->taskTable->resizeColumnsToContents();
    ui->taskTable->horizontalHeader()->setResizeMode(TASK_NAME_COL, QHeaderView::Stretch);
    ui->taskTable->horizontalHeader()->setResizeMode(TASK_EVALUATED_COL, QHeaderView::ResizeToContents);
    ui->taskTable->setStyleSheet("color:#333");
    ui->refreshButton->setIcon(QIcon("Resources/refresh.png"));

    ui->rightWidget->setCurrentIndex(0);
}

TaWindow::~TaWindow()
{
    delete ui;
}

/**
 * Description: Handles the client being disconnected from the server
 * Paramters: None
 * Returns: Void
 */
void TaWindow::connectionDisconnected() {
    logout();
}

/**
 * Description: Creates a new login window and dismisses the TA Window
 * Paramters: PARAMETERS
 * Returns: RETURN
 */
void TaWindow::logout() {

    LoginWindow* loginWindow = new LoginWindow;
    loginWindow->show();

    closeWindow();
}

/**
 * Description: Quits TAEval
 * Paramters: None
 * Returns: Void
 */
void TaWindow::quit() {
    QCoreApplication::exit();
}

/**
 * Description: Unsubscribes TA Window from all updates and closes TA Window
 * Paramters: None
 * Returns: Void
 */
void TaWindow::closeWindow() {
    ConnectionClient::getInstance().unsubscribe(this);
    close();
}

/**
 * Description: Loads course list for a specific TA
 * Paramters: List of courses returned from server
 * Returns: Void
 */
void TaWindow::updateCourseListForTa(QList<Course*> list) {
    courseMap.clear();

    int index = 0;
    foreach(Course* course, list) {
        courseMap.insert(index++, course);
        ui->courseComboBox->addItem(course->getFullCourseName());
    }
    if (courseMap.isEmpty()) {
        ui->refreshButton->setEnabled(false);
    }
}

/**
 * @brief TaWindow::updateTaskListForTaAndCourse
 * @param list
 */
void TaWindow::updateTaskListForTaAndCourse(QList<Task*> list) {
    ui->taskTable->setRowCount(0);

    taskMap.clear();
    foreach(Task* task, list){
        int row = ui->taskTable->rowCount();
        taskMap.insert(row, task);
        ui->taskTable->insertRow(row);
        ui->taskTable->setItem(row, TASK_NAME_COL, new QTableWidgetItem(task->getName()));
        if (task->hasEvaluation()) {
            ui->taskTable->setItem(row, TASK_EVALUATED_COL, new QTableWidgetItem("Evaluated"));
        } else {
            ui->taskTable->setItem(row, TASK_EVALUATED_COL, new QTableWidgetItem(QString("No Evaluation")));
        }

    }
}

/**
 * Description: Makes request for a list of tasks associated with the selected course
 * Paramters: Currently selected course
 * Returns: Void
 */
void TaWindow::selectCourse(Course* course) {

    if (course != NULL) {
        TaControl tc;
        tc.getTaskListForTaAndCourse(getCurrentTa(), course);
    }
    ui->refreshButton->setEnabled(true);

}

/**
 * Description: Displays currently selected task into the task information view
 * Paramters: Currently selected task
 * Returns: Void
 */
void TaWindow::selectTask(Task *task) {
    ui->rightWidget->setCurrentIndex(TASK_INFO_VIEW_INDEX);
    ui->name->setText(task->getName());
    if (task->getDescription().trimmed().compare("") == 0) {
        ui->description->setText("----------");
    } else {
        ui->description->setText(task->getDescription());
    }
    if (task->hasEvaluation()) {
        ui->rating->setText(task->getEvaluation()->getRatingString());
        if (task->getEvaluation()->getComment().trimmed().compare("") == 0) {
            ui->comment->setText("----------");
        } else {
            ui->comment->setText(task->getEvaluation()->getComment());
        }

    } else {
        ui->rating->setText(QString("----------"));
        ui->comment->setText(QString("----------"));
    }
    setCurrentTask(task);
}

/**
 * Description: Handles a new selection from the course combobox
 * Paramters: Selected index from course combobox
 * Returns: Void
 */
void TaWindow::currentCourseComboIndexChanged(int index) {
    selectCourse(courseMap.value(index));
}

/**
 * Description: Makes a request for new information from the server
 * Paramters: None
 * Returns: Void
 */
void TaWindow::refreshButtonReleased() {
    selectCourse(courseMap.value(ui->courseComboBox->currentIndex()));
}

/**
 * Description: Loads the task information view with information based off of the currently selected task
 * Paramters: Selected row number, selected col number
 * Returns: Void
 */
void TaWindow::taskCellClicked(int row, int col) {
    selectTask(taskMap.value(row));
}

