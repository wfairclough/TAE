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
    //ConnectionClient request
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedTaListForInstructorResponse()), this->parent(), SLOT(recievedTaListForInstructor));
    ConnectionClient::getInstance().sendTaForInstructorMessage(uname);
}
