#include "tacontrol.h"
#include "connectionclient.h"

TaControl::TaControl(QObject *parent) :
    QObject(parent)
{
}

/**
 * Description: Send request for list of TAs
 * Paramters: a string the represents the view that wants the information
 * Returns: None
 */
void TaControl::getTas(QString view) {
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedTaListResponse(QString, QList<TeachingAssistant*>)), this->parent(), SLOT(recievedTaList(QString, QList<TeachingAssistant*>)));
    ConnectionClient::getInstance().sendTaListMessage(view);
}

/**
 * Description: Send request for list of Tasks that a TA has
 * Paramters: a string the represents the view that wants the information, the TA whose Tasks you want to see
 * Returns: None
 */
void TaControl::getTaskListForTa(QString view, QString uname) {
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedTaskListForTaResponse(QString, QList<Task*>)), this->parent(), SLOT(recievedTaskListForTa(QString, QList<Task*>)));
    ConnectionClient::getInstance().sendTaskForTa(view, uname);
}

/**
  * Description: Send request to delete a Task from a TA
  * Parameters: a string the represents the view that wants the information, the TA whose Task you want to delete
  * Returns: None
  */
void TaControl::deleteTaskForTA(QString view, QString taskName, QString username) {
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedDeleteTaskForTaResponse(QString, QList<Task*>)), this->parent(), SLOT(recievedDeleteTaskForTa(QString, QList<Task*>)));
    ConnectionClient::getInstance().sendDeleteTaskForTa(view, taskName, username);
}

/**
  * Description: Send request to add a Task from a TA
  * Parameters: a string the represents the view that wants the information, the TA whose Task you want to add and Task info
  * Returns: None
  */
void TaControl::addTaskForTa(QString view, QString uname, QString taskName, QString taskDescription) {
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedAddTaskForTaResponse(QString, QList<Task*>)), this->parent(), SLOT(addDeleteTaskForTa(QString, QList<Task*>)));
    ConnectionClient::getInstance().sendAddTaskForTa(view, taskName, taskDescription, uname);
}
