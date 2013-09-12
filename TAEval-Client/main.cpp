#include <QtGui/QApplication>
#include "loginwindow.h"

/**
 * Description: Main Entry point to the TAEval-Client Application
 * Paramters: Commandline Arguments
 * Returns: int
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    
    return a.exec();
}
