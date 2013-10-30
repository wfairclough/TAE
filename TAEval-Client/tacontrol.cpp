#include "tacontrol.h"
#include "connectionclient.h"

TaControl::TaControl(QObject *parent) :
    QObject(parent)
{
}

/**
 * Description: Send request for list of TAs
 * Paramters:
 * Returns: None
 */
void TaControl::getTas() {
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedTaListResponse(QList<TeachingAssistant*>)), this->parent(), SLOT(recievedTaList(QList<TeachingAssistant*>)));
    ConnectionClient::getInstance().sendTaListMessage();
}

/**
 * Description: Send request for list of Tasks that a TA has
 * Paramters: the TA whose Tasks you want to see
 * Returns: None
 */
void TaControl::getTaskListForTa(QString view, QString uname) {
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedTaskListForTaResponse(QString, QList<Task*>)), this->parent(), SLOT(recievedTaskListForTa(QString, QList<Task*>)));
    ConnectionClient::getInstance().sendTaskForTa(view, uname);
}
