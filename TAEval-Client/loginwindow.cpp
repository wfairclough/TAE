#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "connectionclient.h"
#include "settingsdialog.h"
#include "settings.h"
#include "instructorwindow.h"
#include "tawindow.h"

/**
 * Description: Constructor for the LoginWindow UI
 * Paramters: Parent Widget
 * Returns:
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(sendLoginRequest()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quitTriggered()));
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(settingsTriggered()));

    QRegExp emailRegExp(".*@.*\\..*");

    ui->usernameLineEdit->setValidator(new QRegExpValidator(emailRegExp, this));
    ui->logo->setStyleSheet("background-image: url(Resources/taeval.png)");

    // Load the settings to connect to the server
    loadSettings();

    setStatusBar(new QStatusBar);
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
 * Description:
 * Paramters: None
 * Returns: void
 */
void LoginWindow::sendLoginRequest()
{
    ConnectionClient::getInstance().sendLoginMessage(ui->usernameLineEdit->text());
}

/**
 * @brief LoginWindow::recievedLoginResponse Triggered when login was successful
 * @param user
 */
void LoginWindow::recievedLoginResponse(User* user) {
    qDebug() << "didRecieveLoginResponse";

    statusBar()->clearMessage();

    QString lineEditStyle("QLineEdit {}");
    ui->usernameLineEdit->setStyleSheet(lineEditStyle);

    switch (user->type()) {
    case User::ADMINISTRATOR:
    {
        qDebug() << "Did recieve a ADMINISTRATOR";
        break;
    }
    case User::INSTRUCTOR:
    {
        qDebug() << "Did recieve a Instructor";

        InstructorWindow* window = new InstructorWindow((Instructor*)user);

        window->show();
        hide();

        break;
    }
    case User::TA:
    {
        qDebug() << "Did recieve a TA";

        TaWindow* window = new TaWindow((TeachingAssistant*)user);

        window->show();
        hide();

        break;
    }
    default:
        qDebug() << "Did recieve a NONE";
        break;
    }
}

/**
 * @brief LoginWindow::recievedFailedLoginResponse Triggered when there is a login error
 * @param error
 */
void LoginWindow::recievedFailedLoginResponse(QString error) {
    QString lineEditStyle("QLineEdit {background: #FF8584; color: white;}");
    ui->usernameLineEdit->setStyleSheet(lineEditStyle);

    QString statusBarStyle("QStatusBar {color: red;}");
    statusBar()->setStyleSheet(statusBarStyle);
    statusBar()->showMessage(error);
}

/**
 * @brief LoginWindow::connectionNetworkTimeout Triggered when connection timesout on socket
 */
void LoginWindow::connectionNetworkTimeout()
{
    qDebug() << "Timeout occured on network...";
    ui->loginButton->setEnabled(false);

    QString statusBarStyle("QStatusBar {color: red;}");
    statusBar()->setStyleSheet(statusBarStyle);
    statusBar()->showMessage(host + " unreachable. Got to File -> Settings to edit address.");
}

/**
 * @brief LoginWindow::connectionSuccess triggered when connection is made successfully
 */
void LoginWindow::connectionSuccess()
{
    ui->loginButton->setEnabled(true);
    qDebug() << "Login window connection successful";

    QString statusBarStyle("QStatusBar {color: black;}");
    statusBar()->setStyleSheet(statusBarStyle);
    statusBar()->showMessage("Connected to " + host + " successfully.");
}

/**
 * @brief LoginWindow::loadSettings Load the Settings for the connection from the Settings File
 */
void LoginWindow::loadSettings()
{
    ui->loginButton->setEnabled(false);

    QString settingFileName;

    settingFileName.append(CLIENT_SETTINGS_FILE_NAME);

    QSettings s(settingFileName, QSettings::NativeFormat);
    if (s.contains(CONNECTION_HOST)) {
        host = s.value(CONNECTION_HOST).toString();
        qDebug() << "Using host " << host;
    } else {
        host = "localhost";
        s.setValue(CONNECTION_HOST, host);
        qDebug() << "No host configured using default " << host;
    }

    if (s.contains(CONNECTION_PORT)) {
        port = s.value(CONNECTION_PORT).toInt();
        qDebug() << "Using port " << port;
    } else {
        port = 60004;
        s.setValue(CONNECTION_PORT, port);
        qDebug() << "No post configured using default " << port;
    }


    ConnectionClient::getInstance().connectToServer(host, port);

}


/**
 * @brief LoginWindow::quitTriggered Quit Menu Triggered
 */
void LoginWindow::quitTriggered() {
    QCoreApplication::exit();
}

/**
 * @brief LoginWindow::settingsTriggered Settings Menu Triggered
 */
void LoginWindow::settingsTriggered() {
    SettingsDialog settingsDialog(this);

    settingsDialog.exec();
}





