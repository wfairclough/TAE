#include "tamanager.h"
#include "dbcoordinator.h"
#include <QList>

TaManager::TaManager(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief InstructorManager::fetchAllInstructors
 * @return
 */
QList<TeachingAssistant *> TaManager::fetchAllTas() {
    QList<TeachingAssistant *> list;

    DbCoordinator::getInstance().openDatabase("db/TAEval.db");
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    QSqlQuery allTaQuery(db);
    allTaQuery.prepare("SELECT * FROM ta");
    if(allTaQuery.exec()) {
        while(allTaQuery.next()) {
            int taId = allTaQuery.value(0).toInt();

            QSqlQuery TaQuery(db);
            TaQuery.prepare("SELECT id, firstName, lastName, username, type FROM user WHERE id=?");
            TaQuery.addBindValue(taId);
            if (TaQuery.exec()) {
                while (TaQuery.next()) {
                    int index = 0;
                    TeachingAssistant* ta = new TeachingAssistant();
                    taId = TaQuery.value(index++).toInt();
                    ta->setFirstName(TaQuery.value(index++).toString());
                    ta->setLastName(TaQuery.value(index++).toString());
                    ta->setUsername(TaQuery.value(index++).toString());
                    qDebug() << "Adding TA " << ta->getUsername() << " to list.";
                    list << ta;
                }
            } else {
                qDebug() << "Could not find Teaching Assistant with id " << taId;
            }
        }
    }
    return list;
}

/**
 * @brief TaManager::fetchAllTasksForTeachingAssistance
 * @param instructor
 * @return
 */
QList<Task *> TaManager::fetchAllTasksForTeachingAssistance(TeachingAssistant* ta) {
    QList<Task *> list;

    DbCoordinator::getInstance().openDatabase("db/TAEval.db");
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    QSqlQuery allTaQuery(db);
    allTaQuery.prepare("SELECT id FROM user WHERE username=?");
    allTaQuery.addBindValue(ta->getUsername());
    if(allTaQuery.exec()) {
        while(allTaQuery.next()) {
            qDebug() << "query value: " << allTaQuery.value(0).toInt();
            int taId = allTaQuery.value(0).toInt();
            qDebug() << taId;
            QSqlQuery TaskQuery(db);
            TaskQuery.prepare("SELECT id, name, description, taid, course FROM task WHERE taid=?");
            qDebug() << "task query prep";
            TaskQuery.addBindValue(taId);
            if (TaskQuery.exec()) {
                qDebug() << "task query exec";
                while (TaskQuery.next()) {
                    int index = 0;
                    Task* task = new Task();
                    int taskId = TaskQuery.value(index++).toInt();
                    task->setName(TaskQuery.value(index++).toString());
                    task->setDescription(TaskQuery.value(index++).toString());
                    qDebug() << "Adding Task " << task->getName() << " to list.";
                    list << task;
                }
            } else {
                qDebug() << "Could not find Task with id " << taId;
            }
        }
    }
    return list;
}
