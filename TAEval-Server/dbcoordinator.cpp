#include "dbcoordinator.h"
#include <QDebug>

DbCoordinator::DbCoordinator(QObject *parent) :
    QObject(parent)
{

}


void DbCoordinator::openDatabase(QString dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    bool opened = db.open();

    if (opened) {
        qDebug() << "Opened Database for access.";
    }
}



void DbCoordinator::createDatabase(QString dbName)
{

}
