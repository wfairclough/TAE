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

    connectToServer();
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
    qDebug() << "Bytes avaible for reading from server.";
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

    if (msgType.compare(new QString("Login")) == 0) {
        bool validLogin = false;
        QString userType;

        in >> validLogin;
        in >> userType;

        if (validLogin) {
            qDebug() << "The username and password were correct.";
        }
    }

    nextBlockSize = 0;
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
