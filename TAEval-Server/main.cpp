#include <QtCore/QCoreApplication>
#include "connectionserver.h"
#include "dbcoordinator.h"

/**
 * Description: Main Entry point to the TAEval-Server Application
 * Paramters: Commandline Arguments
 * Returns: int
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConnectionServer server(&a);

    if (!server.listen(QHostAddress::Any, 7290)) {
        qDebug() << "Error: Could not bind to port.";
        return 1;
    }

    DbCoordinator::getInstance().openDatabase(qApp->applicationDirPath() + "/db/", "TAEval.db");

    return a.exec();
}
