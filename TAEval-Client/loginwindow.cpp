#include "loginwindow.h"
#include "ui_loginwindow.h"

/**
 * Description: Constructor for the LoginWindow UI
 * Paramters: Partent Widget
 * Returns: 
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(&clientSocket, SIGNAL(connected()), this, SLOT(connectedToHost()));
    connect(&clientSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect(&clientSocket, SIGNAL(readyRead()), this, SLOT(bytesReady()));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(sendLoginRequest()));

    connectToServer();

    QRegExp emailRegExp(".*@.*\\..*");

    ui->usernameLineEdit->setValidator(new QRegExpValidator(emailRegExp, this));

}

/**
 * Description: Deconstructor for the LoginWindow UI
 * Paramters: None
 * Returns: None
 */
LoginWindow::~LoginWindow()
{
    delete ui;
}


/**
 * Description: Slot triggered by username field when finished editing
 * Paramters: None
 * Returns: void
 */
void LoginWindow::on_usernameLineEdit_lostFocus()
{
    qDebug() << "Username was edited";
    if (ui->usernameLineEdit->hasAcceptableInput()) {
        qDebug() << "Is valid email address";

        QString lineEditStyle("QLineEdit {}");
        ui->usernameLineEdit->setStyleSheet(lineEditStyle);
    } else {
        qDebug() << "invalid email";

        QString lineEditStyle("QLineEdit {background: #FF8584; color: white;}");
        ui->usernameLineEdit->setStyleSheet(lineEditStyle);
    }
}


/**
 * Description:
 * Paramters: None
 * Returns: void
 */
void LoginWindow::connectToServer()
{
    qDebug() << "Connect to server";
    clientSocket.connectToHost("localhost", 7290);

    nextBlockSize = 0;
}



/**
 * Description:
 * Paramters: None
 * Returns: void
 */
void LoginWindow::connectedToHost()
{
    qDebug() << "Connected to host.";
}

/**
 * Description:
 * Paramters: None
 * Returns: void
 */
void LoginWindow::connectionClosedByServer()
{
    qDebug() << "connection is closed.";
    if (nextBlockSize == 0xFFFF)
    {

    }

    closeConnection();
}

void LoginWindow::closeConnection()
{
    clientSocket.close();
}


/**
 * Description:
 * Paramters: None
 * Returns: void
 */
void LoginWindow::bytesReady()
{
    qDebug() << "Bytes avaible for reading from server.";
    QDataStream in(&clientSocket);
    in.setVersion(QDataStream::Qt_4_8);

    if (nextBlockSize == 0) {
        if (clientSocket.bytesAvailable() < sizeof(quint16)) {
            qDebug() << "Message does not have proper header size";
            return;
        }
        in >> nextBlockSize;
    }

    if (clientSocket.bytesAvailable() < nextBlockSize) {
        qDebug() << "Next Block Size is of improper size.";
        return;
    }

    QString msgType;
    bool validLogin = false;

    in >> msgType;

    if (msgType.compare(new QString("Login")) == 0) {
        QString userType;

        in >> validLogin;
        in >> userType;

        if (validLogin) {
            qDebug() << "The username and password were correct.";
        }
    }

    nextBlockSize = 0;
}



/**
 * Description:
 * Paramters: None
 * Returns: void
 */
void LoginWindow::sendLoginRequest()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType("Login");

    QByteArray bytes;
    QDataStream passOut(&bytes, QIODevice::WriteOnly);
    passOut.setVersion(QDataStream::Qt_4_8);
    passOut << ui->passwordLineEdit->text();

    QString password = QString(QCryptographicHash::hash((bytes),QCryptographicHash::Md5));

    out << quint16(0) << msgType << ui->usernameLineEdit->text() << password;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    clientSocket.write(block);

}








