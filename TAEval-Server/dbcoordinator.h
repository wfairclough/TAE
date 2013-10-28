#ifndef DBCOORDINATOR_H
#define DBCOORDINATOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QFile>


class DbCoordinator : public QObject
{
    Q_OBJECT
public:
    DbCoordinator();
    static DbCoordinator& getInstance()
    {
        static DbCoordinator instance;
        return instance;
    }

    void openDatabase(QString dbName);

signals:

public slots:

private:

    DbCoordinator(DbCoordinator const&);
    void operator=(DbCoordinator const&);

    void createDatabase(QString dbName);
    void runSqlScript(QSqlDatabase db, QFile* file);

};

#endif // DBCOORDINATOR_H
