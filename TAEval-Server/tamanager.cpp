#include "tamanager.h"
#include "dbcoordinator.h"
#include <QList>

TaManager::TaManager()
{
}

/**
 * @brief TaManager::fetchAllTeachingAssistants
 * @return
 */
QList<TeachingAssistant *> TaManager::fetchAllTas() {
    QList<TeachingAssistant *> list;

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

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int taId = idForUsername(ta->getUsername());

    if (taId != -1) {
        QSqlQuery TaskQuery(db);
        TaskQuery.prepare("SELECT id, name, description, taid FROM task WHERE taid=?");
        TaskQuery.addBindValue(taId);
        if (TaskQuery.exec()) {
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
    return list;
}

/**
 * @brief TaManager::deleteTaskForTa
 * @return
 */
QList<Task *> TaManager::deleteTaskForTa(Task* task, TeachingAssistant* ta) {
    QList<Task *> list;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int taId = idForUsername(ta->getUsername());

    if (taId != -1) {
        QSqlQuery TaskQuery(db);
        TaskQuery.prepare("SELECT id, name, description, taid FROM task WHERE taid=? AND name=?");
        TaskQuery.addBindValue(taId);
        TaskQuery.addBindValue(task->getName());
        if (TaskQuery.exec()) {
            while (TaskQuery.next()) {
                int index = 0;
                Task* task = new Task();
                int taskId = TaskQuery.value(index++).toInt();
                task->setName(TaskQuery.value(index++).toString());
                task->setDescription(TaskQuery.value(index++).toString());
                qDebug() << "Adding Task " << task->getName() << " to list.";
                list << task;
            }
        }
        QSqlQuery deleteTaskQuery(db);
        deleteTaskQuery.prepare("DELETE FROM task where taid=? AND name=?");
        deleteTaskQuery.addBindValue(taId);
        deleteTaskQuery.addBindValue(task->getName());
        if (deleteTaskQuery.exec()) {
            qDebug() << "Deleted Task Successfully";
        }
    }

    return list;
}


/**
 * @brief TaManager::addTaskForTa
 * @return
 */
QList<Task *> TaManager::addTaskForTa(Task* task, TeachingAssistant* ta) {
    QList<Task *> list;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int taId = idForUsername(ta->getUsername());

    if (taId != -1) {
        QSqlQuery taskQuery(db);
        taskQuery.prepare("INSERT INTO TASK (name, description, taid) VALUES (?, ?, ?)");
        taskQuery.addBindValue(task->getName());
        taskQuery.addBindValue(task->getDescription());
        taskQuery.addBindValue(taId);
        if (taskQuery.exec()) {
            qDebug() << "Task " << task->getName() << " Added";
        }

        list = fetchAllTasksForTeachingAssistance(ta);
    }

    return list;
}


