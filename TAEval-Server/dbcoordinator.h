#ifndef DBCOORDINATOR_H
#define DBCOORDINATOR_H

#include <QObject>
#include <QSqlDatabase>

class DbCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit DbCoordinator(QObject *parent = 0);

    void openDatabase(QString dbName);

signals:

public slots:

private:

    void createDatabase(QString dbName);

};

#endif // DBCOORDINATOR_H
