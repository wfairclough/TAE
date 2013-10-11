#include "connectionserver.h"
#include "connectionthread.h"

ConnectionServer::ConnectionServer(QObject *parent) :
    QTcpServer(parent)
{
}


void ConnectionServer::incomingConnection(int socketDescriptor)
{
    ConnectionThread *thread = new ConnectionThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
