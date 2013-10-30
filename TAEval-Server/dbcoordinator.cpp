#include "dbcoordinator.h"
#include <QDebug>
#include <QSqlQuery>
#include <QTextStream>
#include <QStringList>

/**
 * @brief DbCoordinator::getDatabase
 * @return the opened database
 */
QSqlDatabase DbCoordinator::getDatabase() {
    if (isOpened() == false) {
        qDebug() << "Database has not been opened yet. Please Open." << isOpened();
    }

    return m_db;
}

/**
 * @brief DbCoordinator::openDatabase Open a database or create a new
 * one if non existent.
 * @param dbName the name of the database to open. Relative or Absolute path.
 */
void DbCoordinator::openDatabase(QString dbName)
{
    if (isOpened()) {
        qDebug() << "Database is already opened!";
        return;
    }

    QFile dbFile(dbName);
    bool needsGenerateSchema = false;

    if(!dbFile.exists()) {
        needsGenerateSchema = true;
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbName);
    bool db_opened = m_db.open();

    if (db_opened) {
        qDebug() << "Opened Database for access.";

        if (needsGenerateSchema) {
            qDebug() << "Generating Schema...";

            QFile* file = new QFile(QString("db/TAEval.sql"));
            runSqlScript(m_db, file);

            qDebug() << "Generated DB " << dbName;
        }
        opened = true;
    }
}

/**
 * @brief DbCoordinator::runSqlScript Run all the SQL commands from a file again a database.
 * @param db the database to run the SQL on
 * @param file the SQL script containing the commands.
 */
void DbCoordinator::runSqlScript(QSqlDatabase db, QFile* file) {
    QString script;
    if(file->exists()){
        file->open(QIODevice::Text | QIODevice::ReadOnly);
        QTextStream stream(file);
        script = stream.readAll();

        QSqlQuery query(db);
        QStringList queryes = script.split(QChar(';'));

        foreach(QString queryString, queryes){
            query.exec(queryString);
        }
    }
}



