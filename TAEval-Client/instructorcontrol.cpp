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
void InstructorControl::getTaForInstructor(QString view, QString uname) {
    //ConnectionClient request
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedTaListForInstructorResponse(QString, QList<TeachingAssistant*>)), this->parent(), SLOT(recievedTaListForInstructor(QString, QList<TeachingAssistant*>)));
    ConnectionClient::getInstance().sendTaForInstructorMessage(view, uname);
}
/**
 * Description: Send request for list of Instructor's Courses  ///////////////////////////////////////////////////////ADDED ///////////////////////////////////////////
 * Paramters: username of the Instructor
 * Returns: None
 */

void InstructorControl::getCoursesForInstructor(QString view, Qstring uname) {
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedCourseListForInstructorResponse(QString,QList<Course*>)), this->parent(), SLOT(recievedCourseListForInstructor(QString, QList<Course*>)));
    ConnectionClient::getInstance().sendCourseForInstructorMessage(view, uname);
}

/**
 * Description: Send request for list of Instructors
 * Paramters:
 * Returns: None
 */
void InstructorControl::getInstructors(QString view) {
    //ConnectionClient request
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedInstructorListResponse(QString, QList<Instructor*>)), this->parent(), SLOT(recievedInstructorList(QString, QList<Instructor*>)));
    ConnectionClient::getInstance().sendInstructorListMessage(view);
}
