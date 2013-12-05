#ifndef TIMEOUTSOCKET_H
#define TIMEOUTSOCKET_H

#include <QTcpSocket>
#include <QTimer>

class TimeoutSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TimeoutSocket(QObject *parent = 0);

    void connectToHostWithTimeout(QString host, quint16 port, quint16 timeout);

signals:
    void networkTimeout();

private:
    QTimer *mAuthTimeout;

public slots:
    void connectedToHost();
    void timeoutSlot();

};

#endif // TIMEOUTSOCKET_H
