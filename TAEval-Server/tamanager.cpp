#include "tamanager.h"

TaManager::TaManager(QObject *parent) :
    QObject(parent)
{
}



/**
 * @brief TaManager::fetchAllTasksForTeachingAssistance
 * @param instructor
 * @return
 */
QList<TeachingAssistant *> InstructorManager::fetchAllTasksForTeachingAssistance(TeachingAssistant* ta) {
    QList<Task *> list;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    QSqlQuery courseQuery(db);
    courseQuery.prepare("SELECT id FROM course WHERE instructorId=(SELECT id FROM user WHERE username=?)");
    courseQuery.addBindValue(instructor->getUsername());
    if (courseQuery.exec()) {
        while(courseQuery.next()) {
            int courseId = courseQuery.value(0).toInt();
            qDebug() << "Course ID " << courseId;

            QSqlQuery taCoursesQuery(db);
            taCoursesQuery.prepare("SELECT taId FROM TA_Courses WHERE courseId=?");
            taCoursesQuery.addBindValue(courseId);

            if (taCoursesQuery.exec()) {
                while (taCoursesQuery.next()) {
                    int taId = taCoursesQuery.value(0).toInt();

                    QSqlQuery taQuery(db);
                    taQuery.prepare("SELECT id, firstName, lastName, username, type FROM user WHERE id=?");
                    taQuery.addBindValue(taId);
                    if (taQuery.exec()) {
                        while (taQuery.next()) {
                            int index = 0;
                            TeachingAssistant* ta = new TeachingAssistant();
                            int taId = taQuery.value(index++).toInt();
                            ta->setFirstName(taQuery.value(index++).toString());
                            ta->setLastName(taQuery.value(index++).toString());
                            ta->setUsername(taQuery.value(index++).toString());
                            qDebug() << "Adding TA " << ta->getUsername() << " to list.";
                            list << ta;
                        }
                    } else {
                        qDebug() << "Could not find TAs for Course ID " << courseId;
                    }
                }
            }
        }
    } else {
        qDebug() << "Could not find courses";
    }

    return list;
}


