#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtGui>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void connectToServer();
    void on_usernameLineEdit_lostFocus();
    void connectedToHost();
    void connectionClosedByServer();
    void bytesReady();
    void sendLoginRequest();

private:
    Ui::LoginWindow *ui;

    QTcpSocket clientSocket;
    quint16 nextBlockSize;


    void closeConnection();
    ;

};

#endif // LOGINWINDOW_H
