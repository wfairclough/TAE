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
 * @param path the path to the folder that contains the database
 * @param dbName the name of the database to open. Relative or Absolute path.
 */
void DbCoordinator::openDatabase(QString path, QString dbName)
{
    if (isOpened()) {
        qDebug() << "Database is already opened!";
        return;
    }

    QString dbFilePath(QString(path + "/" + dbName));

    QFile dbFile(dbFilePath);
    bool needsGenerateSchema = false;

    if(!dbFile.exists()) {
        needsGenerateSchema = true;
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbFilePath);
    bool db_opened = m_db.open();

    if (db_opened) {
        qDebug() << "Opened Database for access.";

        opened = true;

        if (needsGenerateSchema) {
            QString schemaFilePath(QString(path + "TAEval.sql"));
            qDebug() << "Generating Schema..." << schemaFilePath;

            QFile* file = new QFile(schemaFilePath);
            runSqlScript(file);

            delete file;

            qDebug() << "Generated DB " << dbName;
        }
    }
}

/**
 * @brief DbCoordinator::runSqlScript Run all the SQL commands from a file again a database.
 * @param db the database to run the SQL on
 * @param file the SQL script containing the commands.
 */
void DbCoordinator::runSqlScript(QFile* file) {
    if (isOpened()) {
        qDebug() << "Open script";
        QString script;
        if(file->exists()){
            file->open(QIODevice::Text | QIODevice::ReadOnly);
            QTextStream stream(file);
            script = stream.readAll();

            QSqlQuery query(m_db);
            qDebug() << "Create Query from database";
            QStringList queryes = script.split(QChar(';'));

            foreach(QString queryString, queryes){
                qDebug() << queryString;
                query.exec(queryString);
            }
        } else {
            qDebug () << "File does not exists";
        }
    } else {
        qDebug() << "Database must be opened first";
    }
}



