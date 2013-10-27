#include "apiwindow.h"
#include "ui_apiwindow.h"

ApiWindow::ApiWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApiWindow)
{
    ui->setupUi(this);
    //connect(ui->callComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateStackIndex(int)));
}

void ApiWindow::updateStackIndex(int index) {
    //ui->stackedWidget->setCurrentIndex(index);
}

ApiWindow::~ApiWindow()
{
    delete ui;
}
