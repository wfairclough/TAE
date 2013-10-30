#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include "teachingassistant.h"
#include "instructor.h"
#include "administrator.h"
#include "task.h"


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
    void sendTaForInstructorMessage(QString view, QString username);
    void sendInstructorListMessage(QString view);
    void sendTaListMessage();
    void sendTaskForTa(QString view, QString uname);

signals:
    void recievedErrorResponse(QString errMsg);
    void recievedLoginResponse(User* user);
    void recievedTaListForInstructorResponse(QString, QList<TeachingAssistant*> list);
    void recievedInstructorListResponse(QString view, QList<Instructor*> list);
    void recievedTaListResponse(QList<TeachingAssistant*> list);
    void recievedTaskListForTaResponse(QString view, QList<Task*> list);

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

