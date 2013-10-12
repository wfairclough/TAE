#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ConnectionClient : public QObject
{
    Q_OBJECT
public:
    static ConnectionClient& getInstance()
    {
        static ConnectionClient instance;
        return instance;
    }

private slots:
    void connectToServer();
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

#endif // CONNECTIONCLIENT_H

