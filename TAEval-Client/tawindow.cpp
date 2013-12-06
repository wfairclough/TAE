#include "tawindow.h"
#include "ui_tawindow.h"

TaWindow::TaWindow(TeachingAssistant* ta, QWidget *parent) :
    teachingAssistant(ta),
    QMainWindow(parent),
    ui(new Ui::TaWindow)
{
    ui->setupUi(this);
}

TaWindow::~TaWindow()
{
    delete ui;
}
