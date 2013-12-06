#include "instructorwindow.h"
#include "ui_instructorwindow.h"

InstructorWindow::InstructorWindow(Instructor* user, QWidget *parent) :
    instructor(user),
    QMainWindow(parent),
    ui(new Ui::InstructorWindow)
{
    ui->setupUi(this);
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}
