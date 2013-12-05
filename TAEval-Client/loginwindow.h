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

private slots:
    void didRecieveLoginResponse(User* user);
    void sendLoginRequest();
    void saveSettings();
    void on_usernameLineEdit_lostFocus();

private:
    Ui::LoginWindow *ui;

};

#endif // LOGINWINDOW_H
