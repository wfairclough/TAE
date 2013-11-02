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
        QString view;
        QString instructorUsername;
        in >> view;
        in >> instructorUsername;
        qDebug() << "View: " << view << " [TaListForInstructorReq] - Instructor: " << instructorUsername;

        InstructorManager im;
        Instructor* i = new Instructor(this);
        i->setUsername(instructorUsername);
        QList<TeachingAssistant*> list = im.fetchAllTeachingAssistanceForInstructor(i);


        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(TA_LIST_FOR_INSTRUCTOR_RSP);

        out << quint16(0) << msgRspType << view << quint16(list.size());

        foreach (TeachingAssistant* ta, list) {
            out << *ta;
        }

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString(COURSE_LIST_FOR_INSTRUCTOR_REQ)) == 0) {
        QString view;
        QString instructorUsername;
        in >> view;
        in >> instructorUsername;
        qDebug() << "View: " << view << " [CourseListForInstructorReq] - Instructor: " << instructorUsername;

        InstructorManager im;
        Instructor* i = new Instructor(this);
        i->setUsername(instructorUsername);
        QList<Course*> list = im.fetchAllCoursesforInstructor(i);

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(COURSE_LIST_FOR_INSTRUCTOR_RSP);

        out << quint16(0) << msgRspType << view << quint16(list.size());
        qDebug() << "|1|";
        foreach (Course* course, list) {
            out << *course;
        }
        qDebug() << "|2|";

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString(INSTRUCTOR_LIST_REQ)) == 0) {
        QString view;
        qDebug() << "[InstructorReq] - All Instructors";
        in >> view;

        InstructorManager im;
        QList<Instructor*> list = im.fetchAllInstructors();


        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(INSTRUCTOR_LIST_RSP);

        out << quint16(0) << msgRspType << view << quint16(list.size());

        foreach (Instructor* prof, list) {
            out << *prof;
        }

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString(TA_LIST_REQ)) == 0) {
        QString view;
        qDebug() << "[TeachingAssistantReq] - All TAs";
        in >> view;

        TaManager tm;
        TeachingAssistant* i = new TeachingAssistant(this);
        QList<TeachingAssistant*> list = tm.fetchAllTas();


        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(TA_LIST_RSP);

        out << quint16(0) << msgRspType << view << quint16(list.size());

        foreach (TeachingAssistant* ta, list) {
            out << *ta;
        }

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString(TASK_LIST_FOR_TA_REQ)) == 0) {
        QString view;
        QString taUsername;
        in >> view;
        in >> taUsername;
        qDebug() << "View: " << view << " [TaskListForTA] - Teaching Assistant: " << taUsername;

        TaManager tm;
        TeachingAssistant* ta = new TeachingAssistant(this);
        ta->setUsername(taUsername);
        QList<Task*> list = tm.fetchAllTasksForTeachingAssistance(ta);


        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(TASK_LIST_FOR_TA_RSP);

        out << quint16(0) << msgRspType << view << quint16(list.size());

        foreach (Task* task, list) {
            qDebug() << " Sending Task ID" << task->getIdString();
            qDebug() << " 2Sending Task ID" << task->getId();
            out << *task;
        }

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString(DELETE_TASK_FOR_TA_REQ)) == 0) {
        QString view;
        QString taskName;
        QString taUsername;
        in >> view;
        in >> taskName;
        in >> taUsername;
        qDebug() << "View: " << view << " [DELETE_TASK_FOR_TA_RSP] - Teaching Assistant: " << taUsername << " Task: " << taskName;

        TaManager tm;
        Task* task = new Task(this);
        task->setName(taskName);
        TeachingAssistant* ta = new TeachingAssistant(this);
        ta->setUsername(taUsername);
        QList<Task*> list = tm.deleteTaskForTa(task, ta);


        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(DELETE_TASK_FOR_TA_RSP);

        out << quint16(0) << msgRspType << view << quint16(list.size());

        foreach (Task* task, list) {
            out << *task;
        }

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);

    } else if (msgType.compare(QString(NEW_TASK_REQ)) == 0) {
        QString view;
        QString taUsername;
        QString taskName;
        QString description;
        Course* course = new Course(this);

        in >> view >> taUsername >> *course >> taskName >> description;

        qDebug() << "View: " << view << " [NEW_TASK_REQ] - Teaching Assistant: " << taUsername << " Task: " << taskName << " " << description << "  cOurse " << course->getName() << course->getSemesterTypeString() << course->getYear();

        TaManager tm;
        Task* task = new Task(this);
        task->setName(taskName);
        task->setDescription(description);

        // Call Data Access
        QList<Task*> list = tm.addTaskForTACourse(task, taUsername, course);


        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);

        QString msgRspType(NEW_TASK_RSP);

        out << quint16(0) << msgRspType << view << quint16(list.size());

        foreach (Task* task, list) {
            qDebug() << "[" << NEW_TASK_RSP << "] task with name " << task->getName() << "   " <<  task->getId();
            out << *task;
        }

        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        tcpSocket.write(block);



    } else if (msgType.compare(QString("test")) == 0) {
        TeachingAssistant i;
        in >> i;
        qDebug() << "TA: " << i.getFirstName() << " " << i.getLastName() << " " << i.getUsername();
    }

    if (tcpSocket.bytesAvailable() > 0) {
        nextBlockSize = 0;
        readClient();
    }

    qDebug() << "Message: " << msgType;

    // Need to check if there is any more messages on the socket
    if (tcpSocket.bytesAvailable() > 0) {
        nextBlockSize = 0;
        readClient();
    }

    nextBlockSize = 0;
}

void ConnectionThread::clientDisconnected()
{
    threadAlive = false;
    qDebug() << "Client has disconnected.";
}







