#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "timeoutsocket.h"


class ConnectionThread : public QThread
{
    Q_OBJECT
public:
    explicit ConnectionThread(int sd, QObject *parent = 0);

    void run();

    signals:
        void error(QTcpSocket::SocketError socketError);

    private slots:

        void connectedToClient();
        void readClient();
        void clientDisconnected();

    private:
        int socketDescriptor;
        TimeoutSocket tcpSocket;
        quint16 nextBlockSize;
        bool threadAlive;
    
};

#endif // CONNECTIONTHREAD_H
