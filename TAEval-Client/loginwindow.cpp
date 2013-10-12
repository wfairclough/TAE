#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "instructor.h"
#include "teachingassistant.h"

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

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(saveSettings()));

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
void LoginWindow::sendLoginRequest()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    QString msgType("test");

    TeachingAssistant ta(10, "Will", "Fairclough", ui->usernameLineEdit->text());

    out << quint16(0) << msgType << ta;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

//    clientSocket.write(block);

}

void LoginWindow::saveSettings()
{
    QSettings s(QString("taeval.cfg"), QSettings::NativeFormat);

    s.setValue("connection/host", ui->usernameLineEdit->text());
    s.setValue("connection/port", 7290);

}






