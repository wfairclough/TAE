#include "connectionclient.h"

/**
 * Description: Constructor for the LoginWindow UI
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

    if (msgType.compare(new QString("LoginRsp")) == 0) {
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

    QString msgType("LoginReq");

    out << quint16(0) << msgType << username;

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
