#include "instructormanager.h"
#include "dbcoordinator.h"

InstructorManager::InstructorManager(QObject *parent) :
    QObject(parent)
{
}


/**
 * @brief TaManager::fetchAllTeachingAssistanceForInstructor
 * @param instructor
 * @return
 */
QList<TeachingAssistant *> InstructorManager::fetchAllTeachingAssistanceForInstructor(Instructor* instructor) {
    QList<TeachingAssistant *> list;

    DbCoordinator::getInstance().openDatabase("db/TAEval.db");
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    QSqlQuery query(db);
    query.prepare("SELECT id FROM user WHERE username=?");
    query.addBindValue(instructor->getUsername());
    query.exec();

    while (query.next()) {
        int id = query.value(0).toInt();
        qDebug() << "ID " << id;
    }

    return list;
}


