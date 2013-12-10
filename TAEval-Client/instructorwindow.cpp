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

    QAction* whatsThisAction = QWhatsThis::createAction(this);

    ui->menuHelp->addAction(whatsThisAction);


}

/**
 * Description: Unsubscribes window from updates and closes window
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::closeWindow() {
    ConnectionClient::getInstance().unsubscribe(this);
    close();
}

/**
 * Description: Handles disconnect from server
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::connectionDisconnected() {
    logout();
}

/**
 * Description: Opens a new login windo and closes instructor window
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::logout() {

    LoginWindow* loginWindow = new LoginWindow;
    loginWindow->show();

    closeWindow();
}

/**
 * Description: Quits application
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::quit() {
    QCoreApplication::exit();
}


// Public Functions
/**
 * Description: Displays tasks for a specific TA and Course that have been returned by the server
 * Paramters: List of tasks returned from server
 * Returns: Void
 */
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

/**
 * Description: Displays TAs for a specific course that have been returned by the server
 * Paramters: List of TAs
 * Returns: Void
 */
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

/**
 * Description: Displays courses for a specific instructor that have been returned by the server
 * Paramters: List of courses
 * Returns: Void
 */
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

}

/**
 * Description: Displays a task that was updated in the server
 * Paramters: The task that was updated
 * Returns: Void
 */
void InstructorWindow::updateTask(Task* task) {
    setCurrentTask(task);
    TaControl tc;
    tc.getTaskListForTaAndCourse(getCurrentTa(), getCurrentCourse());
    selectTask(getCurrentTask());
}


// Private Slots
/**
 * Description: Loads new list of courses when the course combobox is changed
 * Paramters: Index of the selected course
 * Returns: Void
 */
void InstructorWindow::currentCourseComboIndexChanged(int index) {
    if (index != 0) {
        ui->newButton->setEnabled(false);
        ui->newButton4->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->editButton->setEnabled(false);
    } else {
        ui->newButton->setEnabled(true);
        ui->newButton4->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->editButton->setEnabled(true);
    }
    selectCourse(courseMap.value(index));
}

/**
 * Description: Asks for the most up to date list of courses from the server when the refresh button is pressed
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::refreshButtonReleased() {
    selectCourse(getCurrentCourse());
}

/**
 * Description: Disables or enables the task comment box when the rating combobox is changed
 * Paramters: Index of the selected rating
 * Returns: Void
 */
void InstructorWindow::editRatingComboIndexChanged(int index) {
    if (index == 0) {
        ui->editComment->setEnabled(false);
    } else {
        ui->editComment->setEnabled(true);
    }
}

/**
 * Description: Loads tasks associated with the selected TA
 * Paramters: Selected row number, selected column number for taTable
 * Returns: Void
 */
void InstructorWindow::taCellClicked(int row, int col) {
    selectTa(taMap.value(row));
}

/**
 * Description: Loads task information with the selected task
 * Paramters: Selected row number, selected column number for taskTable
 * Returns: RETURN
 */
void InstructorWindow::taskCellClicked(int row, int col) {
    selectTask(taskMap.value(row));
}

/**
 * Description: Loads the currently selected task into the edit task view
 * Paramters: None
 * Returns: Void
 */
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

/**
 * Description: Loads up the view for the instructor to create a new task
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::switchToNewView() {
    setCurrentTask(NULL);
    switchToEditView();
}

/**
 * Description: Handles when the cancel button on the edit task view is clicked
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::cancelEdit() {
    if (getCurrentTask() == NULL || getCurrentTask()->getId() < 0) {
        selectTa(getCurrentTa());
    } else {
        selectTask(getCurrentTask());
    }
}

/**
 * Description: Removes the selected task from the database
 * Paramters: None
 * Returns: Void
 */
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

/**
 * Description: Updates the currently edited task or adds the newly created task to the database
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::saveTask() {
    if (validateFields()) {
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
}


// Private Functions
/**
 * Description: Sets all default styling when instructor view is first loaded
 * Paramters: None
 * Returns: Void
 */
void InstructorWindow::initInstructorView() {
    ui->taTable->horizontalHeader()->setResizeMode(TA_COL_NAME, QHeaderView::Stretch);
    ui->taTable->horizontalHeader()->setResizeMode(TA_COL_RATING, QHeaderView::ResizeToContents);
    ui->taTable->setStyleSheet("color:#333");

    ui->taskTable->horizontalHeader()->setResizeMode(TASK_COL_NAME, QHeaderView::Stretch);
    ui->taskTable->horizontalHeader()->setResizeMode(TASK_COL_EVALUATED, QHeaderView::ResizeToContents);
    ui->taskTable->setStyleSheet("color:#333");

    setupEditRatingText(QString("No Evaluation"));
    ui->refreshButton->setIcon(QIcon("Resources/refresh.png"));

    ui->rightWidget->setCurrentIndex(0);
}

/**
 * Description: Adds default text to the task rating combobox
 * Paramters: Text of the first item in the list
 * Returns: Void
 */
void InstructorWindow::setupEditRatingText(QString firstItem) {
    ui->editRating->clear();
    ui->editRating->addItem(firstItem);
    ui->editRating->addItem("Poor - 1");
    ui->editRating->addItem("Fair - 2");
    ui->editRating->addItem("Good - 3");
    ui->editRating->addItem("Very Good - 4");
    ui->editRating->addItem("Excellent - 5");
}

/**
 * Description: Makes request for the TAs associated with the selected course
 * Paramters: Selected course from the course combobox
 * Returns: Void
 */
void InstructorWindow::selectCourse(Course *course) {
    if (course != NULL) {
        setCurrentCourse(course);
        InstructorControl ic;
        ic.getTaForCourse(getCurrentCourse());
    }
    ui->taskTable->setRowCount(0);
    taskMap.clear();
    ui->rightWidget->setCurrentIndex(0);
    ui->refreshButton->setEnabled(true);
}

/**
 * Description: Makes a request for the tasks associated with the selected TA
 * Paramters: Selected TA from the taTable
 * Returns: Void
 */
void InstructorWindow::selectTa(TeachingAssistant *ta) {
    if (ta != NULL) {
        TaControl tc;
        tc.getTaskListForTaAndCourse(ta, getCurrentCourse());
        ui->rightWidget->setCurrentIndex(TASK_INFO_NEW_INDEX);
        setCurrentTa(ta);
        setCurrentTask(NULL);
    }
}

/**
 * Description: Populates the task information view with the information of the selected task
 * Paramters: Currently selected task
 * Returns: Void
 */
void InstructorWindow::selectTask(Task* task) {
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
 * Description: Checks the name field of the edit task view to make sure it's not empty
 * Paramters: None
 * Returns: true if fields are non empty, otherwise false
 */
bool InstructorWindow::validateFields() {
    bool valid = true;
    QString redStyle("background: #FF8584; color: white;");

    if (ui->editName->text().trimmed().compare("") == 0) {
        valid = false;
        ui->editName->setStyleSheet(redStyle);
    } else {
        ui->editName->setStyleSheet("");
    }

    return valid;
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}
