#include "connectionthread.h"
#include "instructor.h"
#include "teachingassistant.h"
#include "administrator.h"
#include "dbcoordinator.h"
#include "tamanager.h"
#include "instructormanager.h"
#include "MessageTypes.h"


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


    connectedToClient();
}


void ConnectionThread::run()
{
    while (threadAlive) {
        // Keep thread alive waiting for socket events
    }
}


void ConnectionThread::connectedToClient()
{
    qDebug() << "Server connected to client";


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

    if (msgType.compare(QString(LOGIN_REQ)) == 0) {
        QString username;

        in >> username;

        qDebug() << "Trying to login with username: " << username;

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(LOGIN_RSP);
        bool validLogin = true;

        Administrator admin("Will", "Fairclough", username);

        out << quint16(0) << msgRspType << validLogin << User::ADMINISTRATOR << admin;

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString(TA_LIST_FOR_INSTRUCTOR_REQ)) == 0) {
        QString instructorUsername;
        in >> instructorUsername;
        qDebug() << "[TaListForInstructorReq] - Instructor: " << instructorUsername;

        InstructorManager im;
        Instructor* i = new Instructor(this);
        i->setUsername(instructorUsername);
        QList<TeachingAssistant*> list = im.fetchAllTeachingAssistanceForInstructor(i);


        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(TA_LIST_FOR_INSTRUCTOR_RSP);

        out << quint16(0) << msgRspType << quint16(list.size());

        foreach (TeachingAssistant* ta, list) {
            out << *ta;
        }

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString(INSTRUCTOR_LIST_REQ)) == 0) {
        qDebug() << "[InstructorReq] - All Instructors";

        InstructorManager im;
        Instructor* i = new Instructor(this);
        QList<Instructor*> list = im.fetchAllInstructors();


        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(INSTRUCTOR_LIST_RSP);

        out << quint16(0) << msgRspType << quint16(list.size());

        foreach (Instructor* prof, list) {
            out << *prof;
        }

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString("test")) == 0) {
        TeachingAssistant i;
        in >> i;
        qDebug() << "TA: " << i.getFirstName() << " " << i.getLastName() << " " << i.getUsername();
    }

    qDebug() << "Message: " << msgType;


    nextBlockSize = 0;
}

void ConnectionThread::clientDisconnected()
{
    threadAlive = false;
    qDebug() << "Client has disconnected.";
}







