#ifndef DATAACCESSMANAGER_H
#define DATAACCESSMANAGER_H

#include <QObject>
#include <QtSql>

#include <dbcoordinator.h>
#include <instructor.h>
#include <teachingassistant.h>
#include <course.h>
#include <task.h>
#include <evaluation.h>

class DataAccessManager : public QObject
{
    Q_OBJECT
public:
    explicit DataAccessManager(QObject *parent = 0);

   /**
    * @brief idForUsername get the userId for a username.
    *        Returns -1 if not found.
    * @param username
    * @return
    */
    int idForUsername(QString username);

signals:

public slots:



};

#endif // DATAACCESSMANAGER_H
