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
    void sendTaForInstructorMessage(QString username);
    void sendCourseForInstructorMessage(QString username);
    void sendInstructorListMessage();
    void sendTaListMessage();
    void sendTaskForTa(QString uname);
    void sendGetTaskMapForTa(QString uname);
    void sendTaskForTaAndCourse(TeachingAssistant *ta, Course *courseCourse);
    void sendDeleteTask(Task* task);
    void sendAddTaskForTa(QString taskName, QString taskDescription, QString username, QString courseName, Semester::semester_t sem, int courseYear);
    void sendEvaluationListForTasks(QList<quint32> taskIds);
    void sendUpdateTaskAndEvaluation(Task* task, QString iName, QString taName);

signals:


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

