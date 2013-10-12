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
    void sendLoginRequest();
    void saveSettings();
    void on_usernameLineEdit_lostFocus();

private:
    Ui::LoginWindow *ui;


};

#endif // LOGINWINDOW_H
