#include "tawindow.h"
#include "ui_tawindow.h"

TaWindow::TaWindow(TeachingAssistant* user, QWidget *parent) :
    teachingAssistant(user),
    QMainWindow(parent),
    ui(new Ui::TaWindow)
{
    ui->setupUi(this);

    setWindowTitle("Teaching Assistant: " + user->getFullName());
}

TaWindow::~TaWindow()
{
    delete ui;
}


/**
 * @brief TaWindow::updateTaskListForTa Subscriber method to get the updated task list
 * @param list
 */
void TaWindow::updateTaskListForTa(QList<Task*> list) {

}
