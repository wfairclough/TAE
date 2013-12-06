#include "instructorwindow.h"
#include "ui_instructorwindow.h"

InstructorWindow::InstructorWindow(Instructor* user, QWidget *parent) :
    instructor(user),
    QMainWindow(parent),
    ui(new Ui::InstructorWindow)
{
    ui->setupUi(this);

    setWindowTitle("Instructor: " + user->getFullName());
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}
