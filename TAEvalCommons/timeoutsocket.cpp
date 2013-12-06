#include "timeoutsocket.h"

/**
 * @brief TimeoutSocket::TimeoutSocket
 * @param parent
 */
TimeoutSocket::TimeoutSocket(QObject *parent) :
    QTcpSocket(parent)
{
    mAuthTimeout = new QTimer();
}

/**
 * @brief connectToHost Overridden connectToHost() method to add timeout functionality;
 * @param host
 * @param port
 */
void TimeoutSocket::connectToHostWithTimeout(QString host, quint16 port, quint16 timeout) {
    this->disconnectFromHost();
    close();

    connect(mAuthTimeout, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    connect(this, SIGNAL(connected()), this, SLOT(connectedToHost()));
    mAuthTimeout->start(timeout);

    connectToHost(host, port);
}

/**
 * @brief TimeoutSocket::connectedToHost triggered when connected to host.
 */
void TimeoutSocket::connectedToHost() {
    disconnect(mAuthTimeout, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    disconnect(this, SIGNAL(connected()), this, SLOT(connectedToHost()));

    mAuthTimeout->stop(); // stop the timeout timer
}

/**
 * @brief TimeoutSocket::timeoutSlot
 */
void TimeoutSocket::timeoutSlot() {
    emit networkTimeout();
    disconnect(mAuthTimeout, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    this->disconnectFromHost();
    close();
}
