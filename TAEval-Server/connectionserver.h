#ifndef CONNECTIONSERVER_H
#define CONNECTIONSERVER_H

#include <QTcpServer>

class ConnectionServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ConnectionServer(QObject *parent = 0);
    
signals:
    
public slots:

private:
    void incomingConnection(int sd);

};

#endif // CONNECTIONSERVER_H
