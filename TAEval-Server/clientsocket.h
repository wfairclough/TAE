#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>

#include "databasemanager.h"

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);
    
signals:

private slots:
    void readClient();
    void connectedToClient();

public slots:

private:
    quint16 nextBlockSize;
    DatabaseManager dbm;
    
};

#endif // CLIENTSOCKET_H
