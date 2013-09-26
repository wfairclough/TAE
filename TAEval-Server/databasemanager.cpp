#include "databasemanager.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{

}

bool DatabaseManager::openDB()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

    #ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("taeval.db");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    #else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("taeval.db");
    #endif

    // Open databasee
    return db.open();
}

QSqlError DatabaseManager::lastError()
{
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::deleteDB()
{
    // Close database
    db.close();

    #ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("taeval.db");
    path = QDir::toNativeSeparators(path);
    return QFile::remove(path);
    #else

    // Remove created database binary file
    return QFile::remove("taeval.db");
    #endif
}


int DatabaseManager::insertUser(QString username, QString password)
{
    int newId = -1;
    bool ret = false;

    if (db.isOpen())
    {
        //http://www.sqlite.org/autoinc.html
        // NULL = is the keyword for the autoincrement to generate next value

        QSqlQuery query;

        ret = query.exec(QString("insert into USERS(username, password) values('%1', '%2')").arg(username).arg(password));

        // Get database given autoincrement value
        if (ret)
        {
            // http://www.sqlite.org/c3ref/last_insert_rowid.html
            newId = query.lastInsertId().toInt();
        }

    }
    return newId;
}



bool DatabaseManager::validCredentials(QString username, QString password)
{
    bool ret = false;

    QSqlQuery query(QString("select * from USERS where username = '%1'").arg(username));
    if (query.next())
    {
        QString pass = query.value(2).toString();
        qDebug() << "Password from database " << pass;
        ret = (pass.compare(password) == 0);
    }

    return ret;
}












