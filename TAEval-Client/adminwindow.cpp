#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(Administrator* user, QWidget *parent) :
    administrator(user),
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
