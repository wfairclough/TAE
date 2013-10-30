#include "connectionclient.h"
#include "MessageTypes.h"

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

//    connectToServer();
}

/**
 * Description: Tries to make a connection to the server
 * Paramters:
 * Returns: Void
 */
void ConnectionClient::connectToServer()
{
    qDebug() << "Connecting to server";
    clientSocket.connectToHost("localhost", 7290);

    nextBlockSize = 0;
}

/**
 * Description:
 * Paramters:
 * Returns: Void
 */
void ConnectionClient::connectedToHost()
{
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
                Administrator admin;
                in >> admin;
                emit recievedLoginResponse(&admin);
                break;
            }
            case User::INSTRUCTOR:
            {
                Instructor instructor;
                in >> instructor;
                emit recievedLoginResponse(&instructor);
                break;
            }
            case User::TA:
            {
                qDebug() << "emit recievedLoginResponse";
                TeachingAssistant ta;
                in >> ta;
                emit recievedLoginResponse(&ta);
                break;
            }
            default:
                break;
            }
        } else {
            emit recievedErrorResponse(QString("Not a valid username in the system."));
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
        }
        emit recievedTaListForInstructorResponse(list);

    } else if (msgType.compare(QString(INSTRUCTOR_LIST_RSP)) == 0) {
        QList<Instructor*> list;
        quint16 listSize = 0;
        in >> listSize;
        for(int i = 0; i < listSize; i++) {
            // Find proper place to delete pointers later. Possibly in the view.
            Instructor *prof = new Instructor();
            in >> *prof;
            list << prof;
        }
        emit recievedInstructorListResponse(list);

    } else if (msgType.compare(QString(TA_LIST_RSP)) == 0) {
        QList<TeachingAssistant*> list;
        quint16 listSize = 0;
        in >> listSize;
        for(int i = 0; i < listSize; i++) {
            // Find proper place to delete pointers later. Possibly in the view.
            TeachingAssistant *ta = new TeachingAssistant();
            in >> *ta;
            list << ta;
        }
        emit recievedTaListResponse(list);

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

    qDebug() << "Wrote Data to server.";
}

/**
 * Description: Send a message to the server asking for a list of TA's for a particular Instructor
 * Paramters: the Instructors username
 * Returns: Void
 */
void ConnectionClient::sendTaForInstructorMessage(QString username){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(TA_LIST_FOR_INSTRUCTOR_REQ);

    out << quint16(0) << msgType << username;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote Data to server.";
}

/**
 * Description: Send a message to server asking for all Instructors
 * Paramters: None
 * Returns: Void
 */
void ConnectionClient::sendInstructorListMessage(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(INSTRUCTOR_LIST_REQ);

    out << quint16(0) << msgType;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote Data to server.";
}

/**
 * Description: Send a message to server asking for all Tas
 * Paramters: None
 * Returns: Void
 */
void ConnectionClient::sendTaListMessage(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType(TA_LIST_REQ);

    out << quint16(0) << msgType;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

    qDebug() << "Wrote Data to server.";
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


QDataStream& operator >>(QDataStream& in, User::user_t& e)
{
    //This also works, but I would love to one-line it
    quint32 buffer;
    in >> buffer;
    e = User::user_t(buffer);

    return in;
}
