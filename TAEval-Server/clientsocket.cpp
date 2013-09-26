#include "clientsocket.h"


ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(connected()), this, SLOT(connectedToClient()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

    nextBlockSize = 0;
    qDebug() << "Setup connection to client";

    if (dbm.openDB()) {
        qDebug() << "Database is open for access";
    }
}


void ClientSocket::readClient()
{
    qDebug() << "Read from client";

    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_8);

    if (nextBlockSize == 0) {
        if (bytesAvailable() < sizeof(quint16)) {
            qDebug() << "Message does not have proper header size";
            return;
        }
        in >> nextBlockSize;
    }

    if (bytesAvailable() < nextBlockSize) {
        qDebug() << "Next Block Size is of improper size.";
        return;
    }

    QString msgType;
    QString username;
    QString password;

    bool validLogin = false;

    in >> msgType;

    if (msgType.compare(new QString("Login")) == 0) {
        qDebug() << "Message is of login type";
        in >> username >> password;

        qDebug() << "Username: " << username << " Password: " << password;

        //int rc = dbm.insertUser(username, password);
        //qDebug() << "Inserted new user " << rc;
        validLogin = dbm.validCredentials(username, password);
        if (validLogin) {
            qDebug() << "Username and password were correct";
        }
        else
        {
            qDebug() << "The username or password was incorrect";
        }

    }

    qDebug() << "Message: " << msgType;


    nextBlockSize = 0;


    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);



    out << quint16(0) << msgType << validLogin << 0xFFFF;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    this->write(block);

}

void ClientSocket::connectedToClient()
{
    qDebug() << "Connection established to client";
}
