#include "connectionthread.h"
#include "authenticationmanager.h"
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
        QString username;
        QString password;
        bool validLogin = false;

        qDebug() << "Message is of login type";
        in >> username >> password;

        qDebug() << "Username: " << username << " Password: " << password;

        AuthenticationManager am;
        connect(&am, SIGNAL(validatedUserCredentials(bool,QString)), this, SLOT(didVerifyUserCredentials(bool,QString)));

        am.validateUserCredentials(username, password);

    }

    qDebug() << "Message: " << msgType;


    nextBlockSize = 0;
}

void ConnectionThread::clientDisconnected()
{
    threadAlive = false;
}


/*==========Authentication Manager============*/

void ConnectionThread::didVerifyUserCredentials(bool isValid, QString userType)
{
    qDebug() << "Write didVerifyUserCredentials to Client";

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType("Login");

    out << quint16(0) << msgType << isValid << userType;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    tcpSocket.write(block);

}





