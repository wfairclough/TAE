#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "connectionclient.h"

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

    QRegExp emailRegExp(".*@.*\\..*");

    ui->usernameLineEdit->setValidator(new QRegExpValidator(emailRegExp, this));

    ConnectionClient::getInstance().connectToServer();
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
void LoginWindow::sendLoginRequest()
{
    connect(&ConnectionClient::getInstance(), SIGNAL(recievedLoginResponse(User*)), this, SLOT(didRecieveLoginResponse(User*)));

    ConnectionClient::getInstance().sendLoginMessage(ui->usernameLineEdit->text());
}

void LoginWindow::didRecieveLoginResponse(User* user) {
    disconnect(&ConnectionClient::getInstance(), SIGNAL(recievedLoginResponse(User*)), this, SLOT(didRecieveLoginResponse(User*)));

    qDebug() << "didRecieveLoginResponse";

    switch (user->type()) {
    case User::ADMINISTRATOR:
    {
        qDebug() << "Did recieve a ADMINISTRATOR";
        break;
    }
    case User::INSTRUCTOR:
    {
        qDebug() << "Did recieve a Instructor";
        break;
    }
    case User::TA:
    {
        qDebug() << "Did recieve a TA";
        break;
    }
    default:
        qDebug() << "Did recieve a NONE";
        break;
    }

}

void LoginWindow::saveSettings()
{
    QString settingFileName;

#if defined(Q_OS_DARWIN)
    settingFileName.append("taeval.plist");
#elif defined(Q_OS_UNIX)
    settingFileName.append("taeval.cfg");
#else
#error "We don't support that version yet..."
#endif

    QSettings s(settingFileName, QSettings::NativeFormat);

    s.setValue("connection/host", ui->usernameLineEdit->text());
    s.setValue("connection/port", 7290);

}






