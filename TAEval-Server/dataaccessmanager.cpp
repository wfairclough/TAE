#include "dataaccessmanager.h"

DataAccessManager::DataAccessManager(QObject *parent) :
    QObject(parent)
{

}


/**
 * @brief idForUsername get the userId for a username.
 *        Returns -1 if not found.
 * @param username
 * @return
 */
int DataAccessManager::idForUsername(QString username) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int id = -1;

    QSqlQuery allTaQuery(db);
    allTaQuery.prepare("SELECT id FROM user WHERE username=?");
    allTaQuery.addBindValue(username);
    if(allTaQuery.exec()) {
        while(allTaQuery.next()) {
            id = allTaQuery.value(0).toInt();

        }
    }

    return id;
}

/**
 * @brief teachingAssistantForId Get the Teaching Assistant from
 *        the DB for the id.
 * @param id
 * @return
 */
TeachingAssistant* DataAccessManager::teachingAssistantForId(int id) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    TeachingAssistant* ta;

    QSqlQuery taQuery(db);
    taQuery.prepare("SELECT firstName, lastName, username, type FROM user WHERE id=?");
    taQuery.addBindValue(id);
    if(taQuery.exec()) {
        while(taQuery.next()) {
            int index = 0;
            ta = new TeachingAssistant();
            id = taQuery.value(index++).toInt();
            ta->setFirstName(taQuery.value(index++).toString());
            ta->setLastName(taQuery.value(index++).toString());
            ta->setUsername(taQuery.value(index++).toString());
            break;
        }
    }

    return ta;
}


Instructor* DataAccessManager::instructorForId(int id) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    Instructor* instructor;

    QSqlQuery taQuery(db);
    taQuery.prepare("SELECT firstName, lastName, username, type FROM user WHERE id=?");
    taQuery.addBindValue(id);
    if(taQuery.exec()) {
        while(taQuery.next()) {
            int index = 0;
            instructor = new Instructor();
            id = taQuery.value(index++).toInt();
            instructor->setFirstName(taQuery.value(index++).toString());
            instructor->setLastName(taQuery.value(index++).toString());
            instructor->setUsername(taQuery.value(index++).toString());
            break;
        }
    }

    return instructor;
}



Administrator* DataAccessManager::administratorForId(int id) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    Administrator* administrator;

    QSqlQuery taQuery(db);
    taQuery.prepare("SELECT firstName, lastName, username, type FROM user WHERE id=?");
    taQuery.addBindValue(id);
    if(taQuery.exec()) {
        while(taQuery.next()) {
            int index = 0;
            administrator = new Administrator();
            id = taQuery.value(index++).toInt();
            administrator->setFirstName(taQuery.value(index++).toString());
            administrator->setLastName(taQuery.value(index++).toString());
            administrator->setUsername(taQuery.value(index++).toString());
            break;
        }
    }

    return administrator;
}



/**
 * @brief idForCourse Get the ID for the Course primary keys
 * @param name
 * @param sem
 * @param year
 * @return
 */
int DataAccessManager::idForCourse(QString name, Semester::semester_t sem, int year) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int id = -1;

    QSqlQuery allCourseQuery(db);
    allCourseQuery.prepare("SELECT id FROM course WHERE name=? and semester=? and year=?");
    allCourseQuery.addBindValue(name);
    allCourseQuery.addBindValue(sem);
    allCourseQuery.addBindValue(year);
    if(allCourseQuery.exec()) {
        while(allCourseQuery.next()) {
            id = allCourseQuery.value(0).toInt();
            break;
        }
    }

    return id;
}





int DataAccessManager::idForTask(Task* task) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int id = -1;

    QSqlQuery taskQuery(db);
    taskQuery.prepare("SELECT id FROM task WHERE name=?");
    taskQuery.addBindValue(task->getName());
    if(taskQuery.exec()) {
        while(taskQuery.next()) {
            id = taskQuery.value(0).toInt();
            break;
        }
    }

    return id;
}



