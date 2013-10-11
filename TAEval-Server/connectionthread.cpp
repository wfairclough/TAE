#include "connectionthread.h"
#include "instructor.h"
#include "teachingassistant.h"

#include <QDataStream>


ConnectionThread::ConnectionThread(int sd, QObject *parent) :
    QThread(parent),
    socketDescriptor(sd),
    threadAlive(true)
{
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
    }

    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(connectedToClient()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    nextBlockSize = 0;
    qDebug() << "Setup connection to client";

}


void ConnectionThread::run()
{
    while (threadAlive) {
        // Keep thread alive waiting for socket events
    }
}


void ConnectionThread::connectedToClient()
{

}

void ConnectionThread::readClient()
{
    qDebug() << "Read from client";

    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_8);

    if (nextBlockSize == 0) {
        if (tcpSocket.bytesAvailable() < sizeof(quint16)) {
            qDebug() << "Message does not have proper header size";
            return;
        }
        in >> nextBlockSize;
    }

    if (tcpSocket.bytesAvailable() < nextBlockSize) {
        qDebug() << "Next Block Size is of improper size.";
        return;
    }

    QString msgType;



    in >> msgType;

    if (msgType.compare(new QString("Login")) == 0) {


    } else if (msgType.compare(new QString("test")) == 0) {
        TeachingAssistant i;
        in >> i;
        qDebug() << "TA: " << i.getId() << " " << i.getFirstName() << " " << i.getLastName() << " " << i.getUsername();
    }

    qDebug() << "Message: " << msgType;


    nextBlockSize = 0;
}

void ConnectionThread::clientDisconnected()
{
    threadAlive = false;
    qDebug() << "Client has disconnected.";
}




