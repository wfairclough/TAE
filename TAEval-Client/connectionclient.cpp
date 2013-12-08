#include "connectionclient.h"
#include "MessageTypes.h"
#include <QDataStream>

/**
 * Description: Constructor for the ConnectionClient
 * Paramters: Partent Widget
 * Returns:
 */
ConnectionClient::ConnectionClient()
{
    connect(&clientSocket, SIGNAL(connected()), this, SLOT(connectedToHost()));
    connect(&clientSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect(&clientSocket, SIGNAL(readyRead()), this, SLOT(bytesReady()));
    connect(&clientSocket, SIGNAL(networkTimeout()), this, SLOT(recievedNetworkTimeout()));
}

/**
 * Description: Tries to make a connection to the server
 * Paramters:
 * Returns: Void
 */
void ConnectionClient::connectToServer(QString host, quint16 port)
{
    qDebug() << "Connecting to server";
    clientSocket.connectToHostWithTimeout(host, port, 5000);

    nextBlockSize = 0;
}

/**
 * @brief ConnectionClient::recievedNetworkTimeout Triggered when a network timeout occured on the socket
 */
void ConnectionClient::recievedNetworkTimeout()
{
    // Update all the subscribers
    foreach (AbstractSubscriber* subscriber , subscriberList) {
        subscriber->connectionNetworkTimeout();
    }
}

/**
 * Description:
 * Paramters:
 * Returns: Void
 */
void ConnectionClient::connectedToHost()
{
    // Update all the subscribers
    foreach (AbstractSubscriber* subscriber , subscriberList) {
        subscriber->connectionSuccess();
    }
    qDebug() << "Successfully connected to Host";
}

/**
 * Description: SLOT triggered when the clientSocket has bytes availible for reading.
 * Paramters:
 * Returns: Void
 */
void ConnectionClient::bytesReady()
{
    qDebug() << "Bytes available for reading from server.";
    QDataStream in(&clientSocket);
    in.setVersion(QDataStream::Qt_4_8);

    if (nextBlockSize == 0) {
        if (clientSocket.bytesAvailable() < sizeof(quint16)) {
            qDebug() << "Message does not have proper header size";
            return;
        }
        in >> nextBlockSize;
    }

    if (clientSocket.bytesAvailable() < nextBlockSize) {
        qDebug() << "Next Block Size is of improper size.";
        return;
    }

    // Get the message type.
    QString msgType;
    in >> msgType;

    qDebug() << "Got Message Type: " + msgType;

    if (msgType.compare(QString(LOGIN_RSP)) == 0) {
        qDebug() << "Got LoginRsp Message";
        bool validLogin = false;
        User::user_t userType;

        in >> validLogin;
        in >> userType;


        if (validLogin) {
            qDebug() << "Log in was valid with type: " << userType;
            switch (userType) {
            case User::ADMINISTRATOR:
            {
                Administrator* admin = new Administrator;
                in >> *admin;

                foreach (AbstractSubscriber* subscriber , subscriberList) {
                    subscriber->recievedLoginResponse(admin);
                }

                break;
            }
            case User::INSTRUCTOR:
            {
                Instructor* instructor = new Instructor;
                in >> *instructor;

                foreach (AbstractSubscriber* subscriber , subscriberList) {
                    subscriber->recievedLoginResponse(instructor);
                }

                break;
            }
            case User::TA:
            {
                qDebug() << "emit recievedLoginResponse";
                TeachingAssistant* ta = new TeachingAssistant;
                in >> *ta;

                foreach (AbstractSubscriber* subscriber , subscriberList) {
                    subscriber->recievedLoginResponse(ta);
                }

                break;
            }
            default:
                break;
            }
        } else {
            QString errorMessage;
            in >> errorMessage;

            foreach (AbstractSubscriber* subscriber , subscriberList) {
                subscriber->recievedFailedLoginResponse(QString("Not a valid username in the system."));
            }
        }

    } else if (msgType.compare(QString(TA_LIST_FOR_INSTRUCTOR_RSP)) == 0) {

        QList<TeachingAssistant*> list;
        quint16 listSize = 0;

        in >> listSize;
        for(int i = 0; i < listSize; i++) {
            // Find proper place to delete pointers later. Possibly in the view.
            TeachingAssistant *ta = new TeachingAssistant();
            in >> *ta;
            list << ta;

            qDebug() << "[" << TA_LIST_FOR_INSTRUCTOR_RSP << "] Recieved a TA with the ID == " << ta->getId();
        }
//        emit recievedTaListForInstructorResponse(view, list);
        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateTaListForInstructor(list);
        }

    } else if (msgType.compare(QString(COURSE_LIST_FOR_INSTRUCTOR_RSP)) == 0){

        QList<Course*> list;
        quint16 listSize = 0;

        in >> listSize;
        for(int i = 0; i < listSize; i++){
            Course *course = new Course();
            in >> *course;
            list << course;

            qDebug() << "[" << COURSE_LIST_FOR_INSTRUCTOR_RSP << "] Recieved a Course with the Sem == " << course->getName() << course->getSemesterTypeString() << " " << course->getYear() << "  " << course->getSemesterTypeInt();
        }
//        emit recievedCourseListForInstructorResponse(view, list);
        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateCourseListForInstructor(list);
        }

    } else if (msgType.compare(QString(COURSE_LIST_FOR_TA_RSP)) == 0){
        qDebug() << "Parsing Message: " << COURSE_LIST_FOR_TA_RSP;

        QList<Course*> list;
        quint16 listSize = 0;

        in >> listSize;
        for(int i = 0; i < listSize; i++){
            Course *course = new Course();
            in >> *course;
            list << course;

            qDebug() << "[" << COURSE_LIST_FOR_TA_RSP << "] Recieved a Course with the Sem == " << course->getName() << course->getSemesterTypeString() << " " << course->getYear() << "  " << course->getSemesterTypeInt();
        }

        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateCourseListForTa(list);
        }


    } else if (msgType.compare(QString(INSTRUCTOR_LIST_RSP)) == 0) {

        QList<Instructor*> list;
        quint16 listSize = 0;
        in >> listSize;

        for(int i = 0; i < listSize; i++) {
            // Find proper place to delete pointers later. Possibly in the view.
            Instructor *prof = new Instructor();
            in >> *prof;
            list << prof;

            qDebug() << "[" << INSTRUCTOR_LIST_RSP << "] Recieved a Instructor with the ID == " << prof->getId();
        }
//        emit recievedInstructorListResponse(view, list);
        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateInstructorList(list);
        }

    } else if (msgType.compare(QString(TA_LIST_RSP)) == 0) {

        QList<TeachingAssistant*> list;
        quint16 listSize = 0;

        in >> listSize;
        for(int i = 0; i < listSize; i++) {
            // Find proper place to delete pointers later. Possibly in the view.
            TeachingAssistant *ta = new TeachingAssistant();
            in >> *ta;
            list << ta;

            qDebug() << "[" << TA_LIST_RSP << "] Recieved a TA with the ID == " << ta->getId();
        }
//        emit recievedTaListResponse(view, list);
        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateTaList(list);
        }

    } else if (msgType.compare(QString(TASK_LIST_FOR_TA_RSP)) == 0) {

        QList<Task*> list;
        quint16 listSize = 0;

        in >> listSize;
        for(int i = 0; i < listSize; i++) {
            // Find proper place to delete pointers later. Possibly in the view.
            Task *task = new Task();
            in >> *task;
            list << task;

            qDebug() << "[" << TASK_LIST_FOR_TA_RSP << "] Recieved a Task with the ID == " << task->getId();
        }
//        emit recievedTaskListForTaResponse(view, list);
        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateTaskListForTa(list);
        }

    } else if (msgType.compare(QString(NEW_TASK_RSP)) == 0) {

        QList<Task*> list;
        quint16 listSize = 0;

        in >> listSize;
        for(int i = 0; i < listSize; i++) {
            // Find proper place to delete pointers later. Possibly in the view.
            Task *task = new Task();
            in >> *task;
            list << task;

            qDebug() << "[" << NEW_TASK_RSP << "] Recieved a Task with the ID == " << task->getId();
        }

        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateAddTaskForTa(list);
        }

    } else if (msgType.compare(QString(EVALUATION_LIST_FOR_TASKS_RSP)) == 0) {

        QList<Evaluation*> list;
        quint16 listSize = 0;

        in >> listSize;

        for(int i = 0; i < listSize; i++) {
            Evaluation* eval = new Evaluation();
            in >> *eval;
            list << eval;

            qDebug() << "[" << EVALUATION_LIST_FOR_TASKS_RSP << "] Recieved an Evaluation with the ID == " << eval->getId() << " and rating: " << eval->getRating();
        }

        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateEvaluationListForTasks(list);
        }
    } else if (msgType.compare(QString(TASK_LIST_FOR_TA_AND_COURSE_RSP)) == 0) {

        QList<Task*> list;
        quint16 listSize = 0;

        in >> listSize;
        for(int i = 0; i < listSize; i++) {
            // Find proper place to delete pointers later. Possibly in the view.
            Task *task = new Task();
            in >> *task;
            list << task;

            qDebug() << "[" << TASK_LIST_FOR_TA_AND_COURSE_RSP << "] Recieved a Task with the ID == " << task->getId();
        }

        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateTaskListForTaAndCourse(list);
        }
    } else if (msgType.compare(QString(UPDATE_TASK_AND_EVALUATION_RSP)) == 0) {

        Task* task = new Task;
        in >> *task;

        foreach (AbstractSubscriber* subscriber , subscriberList) {
            subscriber->updateTask(task);
        }
    }

    if (clientSocket.bytesAvailable() > 0) {
        nextBlockSize = 0;
        bytesReady();
    }


    // Need to check if there is any more messages on the socket
    if (clientSocket.bytesAvailable() > 0) {
        nextBlockSize = 0;
        bytesReady();
    }

    nextBlockSize = 0;
}

/**
 * Description: Send a login message to the server with the username
 * Paramters:
 * Returns: Void
 */
void ConnectionClient::sendLoginMessage(QString username)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(LOGIN_REQ);

    out << quint16(0) << msgType << username;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote LOGIN_REQ Data to server.";
}

/**
 * Description: Send a message to the server asking for a list of TA's for a particular Instructor
 * Paramters: the Instructors username
 * Returns: Void
 */
void ConnectionClient::sendTaForInstructorMessage(QString username) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(TA_LIST_FOR_INSTRUCTOR_REQ);

    out << quint16(0) << msgType << username;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote TA_LIST_FOR_INSTRUCTOR_REQ Data to server.";
}

/**
 * Description: Send a message to the server asking for a list of Course's for a particular Instructor
 * Paramters: the Instructors username
 * Returns: Void
 */
void ConnectionClient::sendCourseForInstructorMessage(QString username){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(COURSE_LIST_FOR_INSTRUCTOR_REQ);

    out << quint16(0) << msgType << username;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));;

    clientSocket.write(block);

    qDebug() << "wrote Data to Server";
}

/**
 * Description: Send a message to the server asking for a list of Course's for a particular Instructor
 * Paramters: the Instructors username
 * Returns: Void
 */
void ConnectionClient::sendCourseForTeachingAssistantMessage(TeachingAssistant* ta) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(COURSE_LIST_FOR_TA_REQ);

    out << quint16(0) << msgType << *ta;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));;

    clientSocket.write(block);

    qDebug() << "wrote [" << COURSE_LIST_FOR_TA_REQ << "]: Data to Server";
}

/**
 * Description: Send a message to server asking for all Instructors
 * Paramters: None
 * Returns: Void
 */
void ConnectionClient::sendInstructorListMessage() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(INSTRUCTOR_LIST_REQ);

    out << quint16(0) << msgType;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote INSTRUCTOR_LIST_REQ Data to server.";
}

/**
 * Description: Send a message to server asking for all Tas
 * Paramters: None
 * Returns: Void
 */
void ConnectionClient::sendTaListMessage() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(TA_LIST_REQ);

    out << quint16(0) << msgType;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote TA_LIST_REQ Data to server.";
}

/**
 * Description: Send a message to server asking for all Tasks for a TA
 * Paramters: view that made the call, username of TA
 * Returns: Void
 */
void ConnectionClient::sendTaskForTa(QString uname) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(TASK_LIST_FOR_TA_REQ);

    out << quint16(0) << msgType << uname;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote TASK_LIST_FOR_TA_REQ Data to server.";
}

/**
 * @brief sendGetTaskMapForTa Send a message to get a Map of Courses and Tasks
 * @param uname
 */
void ConnectionClient::sendGetTaskMapForTa(QString uname) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(TASK_MAP_FOR_TA_REQ);

    out << quint16(0) << msgType << uname;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote " << TASK_MAP_FOR_TA_REQ << "Data to server.";
}

/**
 * @brief sendTaskForTaAndCourse send message to get list of Tasks for a TA and Course
 * @param uname
 */
void ConnectionClient::sendTaskForTaAndCourse(TeachingAssistant* ta, Course* course) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(TASK_LIST_FOR_TA_AND_COURSE_REQ);

    out << quint16(0) << msgType << *ta << *course;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote " << TASK_LIST_FOR_TA_AND_COURSE_REQ << "Data to server.";
}

/**
 * Description: Send a message to server asking to delete Task for a TA
 * Paramters: view that made the call, username of TA
 * Returns: Void
 */
void ConnectionClient::sendDeleteTask(Task *task) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(DELETE_TASK_REQ);

    out << quint16(0) << msgType << *task;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote DELETE_TASK_FOR_TA_REQ Data to server.";
}

/**
 * Description: Send a message to server asking to add Task for a TA
 * Paramters: view that made the call, username of TA
 * Returns: Void
 */
void ConnectionClient::sendAddTaskForTa(QString taskName, QString taskDescription, QString username, QString courseName, Semester::semester_t sem, int courseYear) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(NEW_TASK_REQ);

    Course course;
    course.setName(courseName);
    course.setSemesterType(sem);
    course.setYear(courseYear);

    out << quint16(0) << msgType << username << course << taskName << taskDescription;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote NEW_TASK_REQ Data to server.";
}

/**
 * Description: Send a message to server asking for all Evaluations for Tasks
 * Paramters: view that made the call, ids of Tasks
 * Returns: Void
 */
void ConnectionClient::sendEvaluationListForTasks(QList<quint32> taskIds) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(EVALUATION_LIST_FOR_TASKS_REQ);

    out << quint16(0) << msgType << quint16(taskIds.size());

    foreach (quint32 i, taskIds) {
        out << i;
    }

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote " << EVALUATION_LIST_FOR_TASKS_REQ << " Data to server.";
}

/**
 * Description: Send a message to server requesting an update for the supplied task and evaluation
 * Paramters: view that made the call, username of ta that owns the task, the task to be updated, the evaluation to be updated
 * Returns: Void
 */
void ConnectionClient::sendUpdateTaskAndEvaluation(Task *task, QString iName, QString taName) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(UPDATE_TASK_AND_EVALUATION_REQ);

    out << quint16(0) << msgType << *task << iName << taName;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote " << UPDATE_TASK_AND_EVALUATION_REQ << " Data to server.";
}


/**
 * Description: SLOT thriggers by the server disconnecting.
 * Paramters:
 * Returns: Void
 */
void ConnectionClient::connectionClosedByServer()
{
    qDebug() << "connection is closed.";
    if (nextBlockSize == 0xFFFF)
    {

    }

    closeConnection();
}

/**
 * Description: Closes the Client socket
 * Paramters:
 * Returns: Void
 */
void ConnectionClient::closeConnection()
{
    clientSocket.close();
}

/**
 * @brief ConnectionClient::subscribe Add subscribers to be updated by events
 * @param subscriber
 */
void ConnectionClient::subscribe(AbstractSubscriber* subscriber) {
    subscriberList << subscriber;
}

/**
 * @brief ConnectionClient::unsubscribe Remove subscriber from being updated
 * @param subscriber
 * @return
 */
bool ConnectionClient::unsubscribe(AbstractSubscriber* subscriber) {
    subscriberList.remove(subscriber);
}


QDataStream& operator >>(QDataStream& in, User::user_t& e)
{
    //This also works, but I would love to one-line it
    quint32 buffer;
    in >> buffer;
    e = User::user_t(buffer);

    return in;
}
