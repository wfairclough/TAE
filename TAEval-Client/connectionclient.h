#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QSet>
#include <abstractpublisher.h>
#include <abstractsubscriber.h>
#include "teachingassistant.h"
#include "instructor.h"
#include "administrator.h"
#include "task.h"
#include "evaluation.h"
#include "course.h"
#include "timeoutsocket.h"


class ConnectionClient : public AbstractPublisher
{
    Q_OBJECT
public:
    static ConnectionClient& getInstance()
    {
        static ConnectionClient instance;
        return instance;
    }

    // Abstract Publisher Functions
    void subscribe(AbstractSubscriber* subscriber);
    bool unsubscribe(AbstractSubscriber* subscriber);

    void connectToServer(QString host, quint16 port);

    void sendLoginMessage(QString username);
    void sendTaForInstructorMessage(QString view, QString username);
    void sendCourseForInstructorMessage(QString view, QString username);
    void sendInstructorListMessage(QString view);
    void sendTaListMessage(QString view);
    void sendTaskForTa(QString view, QString uname);
    void sendDeleteTask(QString view, Task* task);
    void sendAddTaskForTa(QString view, QString taskName, QString taskDescription, QString username, QString courseName, Semester::semester_t sem, int courseYear);
    void sendEvaluationListForTasks(QString view, QList<quint32> taskIds);
    void sendUpdateTaskAndEvaluation(QString view, Task* task, QString iName, QString taName);

signals:
    void recievedErrorResponse(QString errMsg);
    void recievedLoginResponse(User* user);
    void recievedTaListForInstructorResponse(QString, QList<TeachingAssistant*> list);
    void recievedCourseListForInstructorResponse(QString,QList<Course*> list);
    void recievedInstructorListResponse(QString view, QList<Instructor*> list);
    void recievedTaListResponse(QString view, QList<TeachingAssistant*> list);
    void recievedTaskListForTaResponse(QString view, QList<Task*> list);
    void recievedAddTaskForTaResponse(QString view, QList<Task*> list);
    void recievedEvaluationListForTasksResponse(QString, QList<Evaluation*> list);


private slots:
    void connectedToHost();
    void connectionClosedByServer();
    void bytesReady();
    void recievedNetworkTimeout();

private:
    ConnectionClient();
    ConnectionClient(ConnectionClient const&);
    void operator=(ConnectionClient const&);

    TimeoutSocket clientSocket;
    quint16 nextBlockSize;

    void closeConnection();
    QSet<AbstractSubscriber*> subscriberList;
    
};

QDataStream& operator >>(QDataStream& in, User::user_t& e);

#endif // CONNECTIONCLIENT_H

