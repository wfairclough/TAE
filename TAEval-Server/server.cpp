#include "server.h"
#include "connectionthread.h"


Server::Server(QObject *parent) :
    QTcpServer(parent)
{

}


void Server::incomingConnection(int socketDescriptor)
{
    ConnectionThread *thread = new ConnectionThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
