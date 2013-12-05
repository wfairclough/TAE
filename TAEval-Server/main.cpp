#include <QtCore/QCoreApplication>
#include "connectionserver.h"
#include "dbcoordinator.h"
#include "settings.h"


/**
 * Description: Main Entry point to the TAEval-Server Application
 * Paramters: Commandline Arguments
 * Returns: int
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QString settingFileName;

    settingFileName.append(SERVER_SETTINGS_FILE_NAME);

    QSettings s(settingFileName, QSettings::NativeFormat);

    QString dbPath;
    QString dbName;
    quint16 port;

    if (s.contains(CONNECTION_PORT)) {
        port = s.value(CONNECTION_PORT).toInt();
        qDebug() << "Using connection port " << port;
    } else {
        port = 60004;
        s.setValue(CONNECTION_PORT, port);
        qDebug() << "No port configured. Using default " << port;
    }


    ConnectionServer server(&a);

    if (!server.listen(QHostAddress::Any, port)) {
        qDebug() << "Error: Could not bind to port.";
        a.exit();
        return -1;
    }

    if (s.contains(DATABASE_PATH)) {
        dbPath = s.value(DATABASE_PATH).toString();
        qDebug() << "Using databse path " << dbPath;
    } else {
        dbPath = qApp->applicationDirPath() + "/db/";
        s.setValue(DATABASE_PATH, dbPath);
        qDebug() << "No database path configured. Using default " << dbPath;
    }

    if (s.contains(DATABASE_NAME)) {
        dbName = s.value(DATABASE_NAME).toString();
        qDebug() << "Using databse name " << dbName;
    } else {
        dbName = "TAEval.db";
        s.setValue(DATABASE_NAME, dbName);
        qDebug() << "No database name configured. Using default " << dbName;
    }

    DbCoordinator::getInstance().openDatabase(dbPath, dbName);

    return a.exec();
}
