#include <QtCore/QCoreApplication>

/**
 * Description: Main Entry point to the TAEval-Server Application
 * Paramters: Commandline Arguments
 * Returns: int
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    return a.exec();
}
