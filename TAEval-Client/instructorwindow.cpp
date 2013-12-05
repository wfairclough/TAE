#include "instructorwindow.h"
#include "ui_instructorwindow.h"

InstructorWindow::InstructorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstructorWindow)
{
    ui->setupUi(this);
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}
