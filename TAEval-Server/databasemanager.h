#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QDir>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

    bool openDB();
    bool deleteDB();
    QSqlError lastError();

    int insertUser(QString username, QString password);
    bool validCredentials(QString username, QString password);

signals:
    
public slots:

private:
    QSqlDatabase db;
    
};

#endif // DATABASEMANAGER_H
