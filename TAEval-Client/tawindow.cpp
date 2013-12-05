#include "tawindow.h"
#include "ui_tawindow.h"

TaWindow::TaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TaWindow)
{
    ui->setupUi(this);
}

TaWindow::~TaWindow()
{
    delete ui;
}
