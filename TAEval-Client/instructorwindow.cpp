#include "instructorwindow.h"
#include "ui_instructorwindow.h"

InstructorWindow::InstructorWindow(Instructor* user, QWidget *parent) :
    instructor(user),
    QMainWindow(parent),
    ui(new Ui::InstructorWindow)
{
    ui->setupUi(this);
    setWindowTitle("Instructor: " + user->getFullName());

    //Style
    ui->taTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->taTable->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
    ui->taskTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->taskTable->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}
