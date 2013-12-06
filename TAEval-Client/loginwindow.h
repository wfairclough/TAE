#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtGui>

#include "user.h"
#include "instructor.h"
#include "teachingassistant.h"
#include "administrator.h"
#include "abstractsubscriber.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow, public AbstractSubscriber
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

    void connectionNetworkTimeout();
    void connectionSuccess();

    void recievedLoginResponse(User* user);
    void recievedFailedLoginResponse(QString error);

    void loadSettings();

private slots:
    void sendLoginRequest();
    void quitTriggered();
    void settingsTriggered();
    void on_usernameLineEdit_lostFocus();

private:
    Ui::LoginWindow *ui;
    QString host;
    quint16 port;

};

#endif // LOGINWINDOW_H
