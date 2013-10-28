#ifndef DBCOORDINATOR_H
#define DBCOORDINATOR_H

#include <QObject>
#include <QSqlDatabase>
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

    void openDatabase(QString dbName);

private:
    DbCoordinator();
    DbCoordinator(DbCoordinator const&);
    void operator=(DbCoordinator const&);

    void createDatabase(QString dbName);
    void runSqlScript(QSqlDatabase db, QFile* file);

};

#endif // DBCOORDINATOR_H
