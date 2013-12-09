#include "instructorcontrol.h"
#include "connectionclient.h"
#include <QDebug>

InstructorControl::InstructorControl(QObject *parent) :
    QObject(parent)
{
}

/**
 * Description: Send request for list of Instructor's TAs
 * Paramters: username of the Instructor
 * Returns: Void
 */
void InstructorControl::getTaForInstructor(QString uname) {
    ConnectionClient::getInstance().sendTaForInstructorMessage(uname);
}

/**
 * Description: Send request for list of Instructor's Courses
 * Paramters: username of the Instructor
 * Returns: Void
 */
void InstructorControl::getCoursesForInstructor(QString uname) {
    ConnectionClient::getInstance().sendCourseForInstructorMessage(uname);
}

/**
 * Description: Send request for list of Instructors
 * Paramters:
 * Returns: Void
 */
void InstructorControl::getInstructors() {
    ConnectionClient::getInstance().sendInstructorListMessage();
}

/**
 * Description: Send request for list of Teaching Assistants for a given course
 * Paramters: the course that is assiciated with the list of TAs
 * Returns: Void
 */
void InstructorControl::getTaForCourse(Course* course) {
    ConnectionClient::getInstance().sendGetTaListForCourse(course);
}
