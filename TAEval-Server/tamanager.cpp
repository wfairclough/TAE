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
                    ta->setId(TaQuery.value(index++).toInt());
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

    if (taId > 0) {
        QSqlQuery taskQuery(db);
        taskQuery.prepare("SELECT id, name, description, taId FROM task WHERE taId=?");
        taskQuery.addBindValue(taId);
        if (taskQuery.exec()) {
            while (taskQuery.next()) {
                int index = 0;
                Task* task = new Task();
                task->setId(taskQuery.value(index++).toInt());
                task->setName(taskQuery.value(index++).toString());
                task->setDescription(taskQuery.value(index++).toString());

                TeachingAssistant* teachingAssistant = teachingAssistantForId(taId);
                task->setTeachingAssistant(teachingAssistant);

                qDebug() << "Adding Task " << task->getId() << " named - " << task->getName() << " to list.";
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

    if (taId > 0) {
        QSqlQuery taskQuery(db);
        taskQuery.prepare("SELECT id, name, description, taId FROM task WHERE taId=? AND name=?");
        taskQuery.addBindValue(taId);
        taskQuery.addBindValue(task->getName());
        if (taskQuery.exec()) {
            while (taskQuery.next()) {
                int index = 0;
                Task* task = new Task();
                task->setId(taskQuery.value(index++).toInt());
                task->setName(taskQuery.value(index++).toString());
                task->setDescription(taskQuery.value(index++).toString());
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
 * @brief TaManager::deleteTask task object must have a valid id.
 * @param task
 * @return
 */
bool TaManager::deleteTask(Task* task) {
    bool rc = false;

    if (task->getId() > 0) {
        QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

        // Cascade delete the evaluations for the task that is being deleted.
        QSqlQuery deleteEvalQuery(db);
        deleteEvalQuery.prepare("DELETE FROM evaluation where taskId=?");
        deleteEvalQuery.addBindValue(task->getId());
        if (deleteEvalQuery.exec()) {
            qDebug() << "Deleted Evaluations for task " << task->getId() << "Successfully";
        } else {
            qDebug() << "Could not cascade delete the evaluations for task. Error Msg: " << deleteEvalQuery.lastError().text();
        }

        // Delete the task after the evaluations have been deleted.
        QSqlQuery deleteTaskQuery(db);
        deleteTaskQuery.prepare("DELETE FROM task where id=?");
        deleteTaskQuery.addBindValue(task->getId());
        if (deleteTaskQuery.exec()) {
            qDebug() << "Deleted Task Successfully";
            rc = true;
        } else {
            qDebug() << "Error: Could not delete Task. Error Msg: " << deleteTaskQuery.lastError().text();
        }
    } else {
        qDebug() << "Task does not have a valid id(" << task->getId() << ")";
    }

    return rc;
}


/**
 * @brief TaManager::addTaskForCourse
 * @return the new list of Tasks for that course
 */
QList<Task *> TaManager::addTaskForTACourse(Task* task, QString taUsername, Course* course) {
    QList<Task *> list;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int courseId = idForCourse(course->getName(), course->getSemesterType(), course->getYear());
    int taId = idForUsername(taUsername);

    if (courseId > 0) { // Check for valid IDs
        QSqlQuery taskQuery(db);
        taskQuery.prepare("INSERT INTO TASK (name, description, courseId, taId) VALUES (?, ?, ?, ?)");
        taskQuery.addBindValue(task->getName());
        taskQuery.addBindValue(task->getDescription());
        taskQuery.addBindValue(courseId);
        taskQuery.addBindValue(taId);

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
        QSqlQuery taskQuery(db);
        taskQuery.prepare("SELECT id, name, description, taId FROM task WHERE courseId=?");
        taskQuery.addBindValue(courseId);
        if (taskQuery.exec()) {
            while (taskQuery.next()) {
                int index = 0;
                Task* task = new Task();
                task->setId(taskQuery.value(index++).toInt());
                task->setName(taskQuery.value(index++).toString());
                task->setDescription(taskQuery.value(index++).toString());


                int taId = taskQuery.value(index++).toInt();

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
 * @brief TaManager::fetchEvaluationsForTasks
 * @param list of tasks
 * @return
 */
QList<Evaluation*> TaManager::fetchEvaluationsForTasks(QList<Task*> tasks) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();
    QList<Evaluation*> evaluationList;
    DataAccessManager dam(this);

    // task is just a fake built task that only includes an id
    // that is why we rebuild the task here.
    foreach (Task* task, tasks) {
        int taskId = task->getId();

        if (taskId != -1) {
            QSqlQuery evaluationQuery(db);
            evaluationQuery.prepare("SELECT id, rating, comment FROM evaluation WHERE taskId=?");
            evaluationQuery.addBindValue(taskId);
            if (evaluationQuery.exec()) {
                if (evaluationQuery.next()) {
                    Evaluation* evaluation = new Evaluation(this);
                    int index = 0;
                    evaluation->setId(evaluationQuery.value(index++).toInt());
                    evaluation->setRating(evaluationQuery.value(index++).toInt());
                    evaluation->setComment(evaluationQuery.value(index++).toString());

                    Task* evalTask = new Task(this);
                    QSqlQuery taQuery(db);
                    taQuery.prepare("SELECT id, name, description, taid FROM task WHERE id=?");
                    taQuery.addBindValue(taskId);
                    if (taQuery.exec()) {
                        taQuery.next();
                        int index = 0;
                        evalTask->setId(taQuery.value(index++).toInt());
                        evalTask->setName(taQuery.value(index++).toString());
                        evalTask->setDescription(taQuery.value(index++).toString());
                        evalTask->setTeachingAssistant(dam.teachingAssistantForId(taQuery.value(index++).toInt()));
                    }
                    evaluation->setTask(evalTask);
                    evaluationList.append(evaluation);
                }
            } else {
                qDebug() << "Could not find Task with id " << taskId;
            }
        }
    }
    qDebug() << "Evaluation List Size: " << evaluationList.size();
    return evaluationList;
}


/**
 * @brief TaManager::deleteEvaluationForTask
 * @param taskId
 * @param eval
 * @return
 */
bool TaManager::deleteEvaluationForTask(int taskId, Evaluation* eval) {
    bool rc = false;

    if (taskId >= 0) {

        QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

        QSqlQuery evaluationQuery(db);
        evaluationQuery.prepare("DELETE FROM evaluation WHERE id=? and taskId=?");
        evaluationQuery.addBindValue(eval->getId());
        evaluationQuery.addBindValue(taskId);

        if (evaluationQuery.exec()) {
            qDebug() << "Successfully delete evaluation.";
            rc = true;
        } else {
            qDebug() << "Error exec new Task SQL: " << evaluationQuery.lastError().text();
        }
    }

    return rc;
}


/**
 * @brief TaManager::deleteEvaluation Evaluation must have a valid Task set with an Id
 * @param eval
 * @return
 */
bool TaManager::deleteEvaluation(Evaluation* eval) {
    bool rc = false;

    if (eval->hasTask()) {

        QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

        QSqlQuery evaluationQuery(db);
        evaluationQuery.prepare("DELETE FROM evaluation WHERE id=? and taskId=?");
        evaluationQuery.addBindValue(eval->getId());
        evaluationQuery.addBindValue(eval->getTask()->getId());

        if (evaluationQuery.exec()) {
            qDebug() << "Successfully delete evaluation.";
            rc = true;
        } else {
            qDebug() << "Error exec new Task SQL: " << evaluationQuery.lastError().text();
        }
    } else {
        qDebug() << "This evaluation does not have a valid Task in its properties";
    }

    return rc;
}



/**
 * @brief TaManager::addEvaluationToTask
 * @param eval
 * @param task
 * @return
 */
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
        qDebug() << "The Task could not be found in the DB";
    }

    return added;
}



/**
 * @brief TaManager::updateTask Update a task and evaluation. The task must have a valid id.
 * @param task to update, evaluation to update
 * @return
 */
bool TaManager::updateTaskAndEvaluation(Task* task, Evaluation* eval) {
    bool added = false;
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();
    DataAccessManager dam(this);

    int taskId = task->getId();
    if (taskId > 0) {
        QSqlQuery taskQuery(db);
        taskQuery.prepare("UPDATE TASK SET name=?, description=? WHERE id=?");
        taskQuery.addBindValue(task->getName());
        taskQuery.addBindValue(task->getDescription());
        taskQuery.addBindValue(task->getId());

        qDebug() << "Updating Task " << task->getIdString() << "in DB";
        added = taskQuery.exec();
        if (added) {
            qDebug() << "Updated Task" << task->getName();
            QSqlQuery evalQuery(db);
            evalQuery.prepare("UPDATE EVALUATION SET rating=?, comment=? WHERE taskid=?");
            evalQuery.addBindValue(eval->getRating());
            evalQuery.addBindValue(eval->getComment());
            evalQuery.addBindValue(task->getId());
            evalQuery.exec();
        } else {
            qDebug() << "Error exec new Task SQL: " << taskQuery.lastError().text();
        }


    } else {
        qDebug() << "The task could not be found in the DB";
    }

    return added;
}






