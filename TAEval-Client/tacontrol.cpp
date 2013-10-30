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
