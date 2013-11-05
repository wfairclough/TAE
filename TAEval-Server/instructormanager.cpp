#include "instructormanager.h"
#include "dbcoordinator.h"
#include <QList>

InstructorManager::InstructorManager()
{
}

/**
 * @brief InstructorManager::fetchAllInstructors
 * @return
 */
QList<Instructor *> InstructorManager::fetchAllInstructors() {
    QList<Instructor *> list;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    QSqlQuery allInstructorQuery(db);
    allInstructorQuery.prepare("SELECT * FROM instructor");
    if(allInstructorQuery.exec()) {
        while(allInstructorQuery.next()) {
            int instructorId = allInstructorQuery.value(0).toInt();

            QSqlQuery instructorQuery(db);
            instructorQuery.prepare("SELECT id, firstName, lastName, username, type FROM user WHERE id=?");
            instructorQuery.addBindValue(instructorId);
            if (instructorQuery.exec()) {
                while (instructorQuery.next()) {
                    int index = 0;
                    Instructor* prof = new Instructor();
                    prof->setId(instructorQuery.value(index++).toInt());
                    prof->setFirstName(instructorQuery.value(index++).toString());
                    prof->setLastName(instructorQuery.value(index++).toString());
                    prof->setUsername(instructorQuery.value(index++).toString());
                    qDebug() << "Adding Instructor " << prof->getUsername() << " to list.";
                    list << prof;
                }
            } else {
                qDebug() << "Could not find Instructor with id " << instructorId;
            }
        }
    }
    return list;
}


/**
 * @brief InstructorManager::fetchAllTeachingAssistanceForInstructor
 * @param instructor
 * @return
 */
QList<TeachingAssistant *> InstructorManager::fetchAllTeachingAssistanceForInstructor(Instructor* instructor) {
    QList<TeachingAssistant *> list;

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
                            ta->setId(taQuery.value(index++).toInt());
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

/**
 * @brief InstructorManager::fetchAllCoursesForInstructor
 * @param instructor
 * @return
 */

QList<Course *> InstructorManager::fetchAllCoursesforInstructor(Instructor *instructor) {
    QList<Course *> list;

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    QSqlQuery courseQuery(db);
    courseQuery.prepare("SELECT id, name, semester, year FROM course WHERE instructorId=(SELECT id FROM user WHERE username=?)");
    courseQuery.addBindValue(instructor->getUsername());
    if (courseQuery.exec()){
        while (courseQuery.next()) {
        int index = 0;
        Course* course = new Course();
        int courseID = courseQuery.value(index++).toInt();
        course->setName(courseQuery.value(index++).toString());
        qDebug() << "GOT A COURSE VALUE OF " << courseQuery.value(index).toInt();
        course->setSemesterType(courseQuery.value(index++).toInt());
        qDebug() << "READ A COURSE VALUE OF " << course->getSemesterTypeInt();
        course->setYear(courseQuery.value(index++).toInt());
        qDebug() << "Adding Course" << course->getName() << ", " << course->getSemesterTypeString() << ", " << course->getYear() << " to list";
        list << course;
        }
    }else {
        qDebug() << "Could not find courses";
    }

    return list;

 }
