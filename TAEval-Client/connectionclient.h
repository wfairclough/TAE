#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "teachingassistant.h"
#include "instructor.h"
#include "teachingassistant.h"
#include "administrator.h"


class ConnectionClient : public QObject
{
    Q_OBJECT
public:
    static ConnectionClient& getInstance()
    {
        static ConnectionClient instance;
        return instance;
    }

    void connectToServer();

    void sendLoginMessage(QString username);

signals:
    void recievedErrorResponse(QString errMsg);
    void recievedLoginResponse(User* user);

private slots:
    void connectedToHost();
    void connectionClosedByServer();
    void bytesReady();

private:
    ConnectionClient();
    ConnectionClient(ConnectionClient const&);
    void operator=(ConnectionClient const&);

    QTcpSocket clientSocket;
    quint16 nextBlockSize;

    void closeConnection();
    
};

QDataStream& operator >>(QDataStream& in, User::user_t& e);

#endif // CONNECTIONCLIENT_H

