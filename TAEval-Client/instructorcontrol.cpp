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
 * Description: Send request for list of Instructors
 * Paramters:
 * Returns: None
 */
void InstructorControl::getInstructors() {
    //ConnectionClient request
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedInstructorListResponse(QList<Instructor*>)), this->parent(), SLOT(recievedInstructorList(QList<Instructor*>)));
    ConnectionClient::getInstance().sendInstructorListMessage();
}
