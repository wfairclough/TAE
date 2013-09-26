#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>

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

    /*==========Authentication Manager============*/
    void didVerifyUserCredentials(bool isValid, QString userType);

private:
    int socketDescriptor;
    QTcpSocket tcpSocket;
    quint16 nextBlockSize;
    bool threadAlive;
    
};

#endif // CONNECTIONTHREAD_H
