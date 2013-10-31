#ifndef DATAACCESSMANAGER_H
#define DATAACCESSMANAGER_H

#include <QObject>
#include <QtSql>

#include <dbcoordinator.h>
#include <instructor.h>
#include <teachingassistant.h>
#include <administrator.h>
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


    /**
     * @brief idForCourse Get the ID for the Course primary keys
     * @param name
     * @param sem
     * @param year
     * @return
     */
    int idForCourse(QString name, Semester::semester_t sem, int year);


    /**
     * @brief idForTask
     * @param task
     * @return
     */
    int idForTask(Task* task);


    /**
     * @brief teachingAssistantForId Get the Teaching Assistant from
     *        the DB for the id.
     * @param id
     * @return
     */
    TeachingAssistant* teachingAssistantForId(int id);


    /**
     * @brief instructorForId
     * @param id
     * @return
     */
    Instructor* instructorForId(int id);


    /**
     * @brief administratorForId
     * @param id
     * @return
     */
    Administrator* administratorForId(int id);


signals:

public slots:



};

#endif // DATAACCESSMANAGER_H
