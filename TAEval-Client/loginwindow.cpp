#include "loginwindow.h"
#include "ui_loginwindow.h"

/**
 * Description: Constructor for the LoginWindow UI
 * Paramters: Partent Widget
 * Returns: 
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

/**
 * Description: Deconstructor for the LoginWindow UI
 * Paramters: None
 * Returns: None
 */
LoginWindow::~LoginWindow()
{
    delete ui;
}
