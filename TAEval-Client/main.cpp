#include <QtGui/QApplication>
#include "apiwindow.h"

/**
 * Description: Main Entry point to the TAEval-Client Application
 * Paramters: Commandline Arguments
 * Returns: int
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApiWindow w;
    w.show();
    
    return a.exec();
}
