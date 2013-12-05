#include <QtGui/QApplication>
#include "loginwindow.h"
#include <connectionclient.h>


/**
 * Description: Main Entry point to the TAEval-Client Application
 * Paramters: Commandline Arguments
 * Returns: int
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;

    ConnectionClient::getInstance().subscribe(&w);

    w.show();

    return a.exec();
}
