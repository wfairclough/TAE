#ifndef DBCOORDINATOR_H
#define DBCOORDINATOR_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QFile>


class DbCoordinator : public QObject
{
    Q_OBJECT
public:

    static DbCoordinator& getInstance()
    {
        static DbCoordinator instance;
        return instance;
    }

    void openDatabase(QString path, QString dbName);
    bool isOpened() { return opened; }
    QSqlDatabase getDatabase();

private:
    DbCoordinator() : opened(false) { }
    DbCoordinator(DbCoordinator const&);
    void operator=(DbCoordinator const&);

    bool opened;
    void runSqlScript(QFile* file);

    QSqlDatabase m_db;
};

#endif // DBCOORDINATOR_H
