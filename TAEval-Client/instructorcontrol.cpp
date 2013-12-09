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
 * Returns: None
 */
void InstructorControl::getTaForInstructor(QString uname) {
    ConnectionClient::getInstance().sendTaForInstructorMessage(uname);
}

/**
 * Description: Send request for list of Instructor's Courses
 * Paramters: username of the Instructor
 * Returns: None
 */

void InstructorControl::getCoursesForInstructor(QString uname) {
    ConnectionClient::getInstance().sendCourseForInstructorMessage(uname);
}

/**
 * Description: Send request for list of Instructors
 * Paramters:
 * Returns: None
 */
void InstructorControl::getInstructors() {
    ConnectionClient::getInstance().sendInstructorListMessage();
}


void InstructorControl::getTaForCourse(Course* course) {
    ConnectionClient::getInstance().sendGetTaListForCourse(course);
}
