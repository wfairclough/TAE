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
            quint32 taId = allTaQuery.value(0).toInt();

            QSqlQuery TaQuery(db);
            TaQuery.prepare("SELECT id, firstName, lastName, username, type FROM user WHERE id=?");
            TaQuery.addBindValue(taId);
            if (TaQuery.exec()) {
                while (TaQuery.next()) {
                    quint32 index = 0;
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
        TaskQuery.prepare("SELECT id, name, description, taId FROM task WHERE taId=?");
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
        TaskQuery.prepare("SELECT id, name, description, taId FROM task WHERE taId=? AND name=?");
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
        deleteTaskQuery.prepare("DELETE FROM task where taId=? AND name=?");
        deleteTaskQuery.addBindValue(taId);
        deleteTaskQuery.addBindValue(task->getName());
        if (deleteTaskQuery.exec()) {
            qDebug() << "Deleted Task Successfully";
        }
    }

    return list;
}


/**
 * @brief TaManager::addTaskForCourse
 * @return the new list of Tasks for that course
 */
QList<Task *> TaManager::addTaskForCourse(Task* task, Course* course) {
    QList<Task *> list;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int courseId = idForCourse(course->getName(), course->getSemesterType(), course->getYear());

    if (courseId != -1) {
        QSqlQuery taskQuery(db);
        taskQuery.prepare("INSERT INTO TASK (name, description, courseId) VALUES (?, ?, ?)");
        taskQuery.addBindValue(task->getName());
        taskQuery.addBindValue(task->getDescription());
        taskQuery.addBindValue(courseId);

        qDebug() << "Adding Task to DB";
        if (taskQuery.exec()) {
            qDebug() << "Task " << task->getName() << " Added";
        } else {
            qDebug() << "Error exec new Task SQL: " << taskQuery.lastError().text();
        }

        list = fetchAllTasksForCourse(course);
    } else {
        qDebug() << "The TA could not be found in the DB";
    }

    return list;
}


/**
 * @brief TaManager::fetchAllTasksForTeachingAssistance
 * @param instructor
 * @return
 */
QList<Task *> TaManager::fetchAllTasksForCourse(Course* course) {
    QList<Task *> list;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int courseId = idForCourse(course->getName(), course->getSemesterType(), course->getYear());

    if (courseId != -1) {
        QSqlQuery TaskQuery(db);
        TaskQuery.prepare("SELECT id, name, description, taId FROM task WHERE courseId=?");
        TaskQuery.addBindValue(courseId);
        if (TaskQuery.exec()) {
            while (TaskQuery.next()) {
                int index = 0;
                Task* task = new Task();
                int taskId = TaskQuery.value(index++).toInt();
                task->setName(TaskQuery.value(index++).toString());
                task->setDescription(TaskQuery.value(index++).toString());


                int taId = TaskQuery.value(index++).toInt();

                TeachingAssistant* ta = teachingAssistantForId(taId);

                task->setTeachingAssistant(ta);
                qDebug() << "Adding Task " << task->getName() << " to list.";
                list << task;
            }
        } else {
            qDebug() << "Could not find Task with id " << courseId;
        }
    }
    return list;
}


/**
 * @brief TaManager::fetchAllTasksForTeachingAssistance
 * @param instructor
 * @return
 */
Evaluation* TaManager::fetchEvaluationForTask(Task* task) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    Evaluation* evaluation;
    int taskId = idForTask(task);

    if (taskId != -1) {
        QSqlQuery evaluationQuery(db);
        evaluationQuery.prepare("SELECT id, rating, comment FROM evaluation WHERE taskId=?");
        evaluationQuery.addBindValue(taskId);
        if (evaluationQuery.exec()) {
            evaluationQuery.next();
            int index = 0;
            int taskId = evaluationQuery.value(index++).toInt();
            evaluation->setRating(evaluationQuery.value(index++).toInt());
            evaluation->setComment(evaluationQuery.value(index++).toString());

            int taId = evaluationQuery.value(index++).toInt();

            TeachingAssistant* ta = teachingAssistantForId(taId);

            task->setTeachingAssistant(ta);
            qDebug() << "Adding Task " << task->getName() << " to list.";
        } else {
            qDebug() << "Could not find Task with id " << taskId;
        }
    }

    return evaluation;
}


bool TaManager::addEvaluationToTask(Evaluation* eval, Task* task) {
    bool added = false;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int taskId = idForTask(task);

    if (taskId != -1) {
        QSqlQuery evaluationQuery(db);
        evaluationQuery.prepare("INSERT INTO EVALUATION (rating, comment, taskId) VALUES (?, ?, ?)");
        evaluationQuery.addBindValue(eval->getRating());
        evaluationQuery.addBindValue(eval->getComment());
        evaluationQuery.addBindValue(taskId);

        qDebug() << "Adding Evaluation to DB";
        added = evaluationQuery.exec();
        if (added) {
            qDebug() << "Evaluation Comment " << eval->getComment() << " Added";
        } else {
            qDebug() << "Error exec new Task SQL: " << evaluationQuery.lastError().text();
        }


    } else {
        qDebug() << "The TA could not be found in the DB";
    }

    return added;
}









