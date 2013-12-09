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


void TaWindow::connectionDisconnected() {
    logout();
}

void TaWindow::logout() {

    LoginWindow* loginWindow = new LoginWindow;
    loginWindow->show();

    closeWindow();
}

void TaWindow::quit() {
    QCoreApplication::exit();
}

void TaWindow::closeWindow() {
    ConnectionClient::getInstance().unsubscribe(this);
    close();
}


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


void TaWindow::selectCourse(Course* course) {

    if (course != NULL) {
        TaControl tc;
        tc.getTaskListForTaAndCourse(getCurrentTa(), course);
    }
    ui->refreshButton->setEnabled(true);

}

void TaWindow::selectTask(Task *task) {
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


void TaWindow::currentCourseComboIndexChanged(int index) {
    selectCourse(courseMap.value(index));
}

void TaWindow::refreshButtonReleased() {
    selectCourse(courseMap.value(ui->courseComboBox->currentIndex()));
}

void TaWindow::taskCellClicked(int row, int col) {
    selectTask(taskMap.value(row));
}

