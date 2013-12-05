#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"


SettingsDialog::SettingsDialog(LoginWindow *parent) :
    loginWindow(parent),
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));

    QString settingFileName;

    settingFileName.append(CLIENT_SETTINGS_FILE_NAME);

    QSettings s(settingFileName, QSettings::NativeFormat);

    QString host;
    quint16 port;

    if (s.contains(CONNECTION_HOST)) {
        host = s.value(CONNECTION_HOST).toString();
        qDebug() << "Using host " << host;
    } else {
        host = "localhost";
        s.setValue(CONNECTION_HOST, host);
        qDebug() << "No host configured using default " << host;
    }

    ui->ipLineEdit->setText(host);

    if (s.contains(CONNECTION_PORT)) {
        port = s.value(CONNECTION_PORT).toInt();
        qDebug() << "Using port " << port;
    } else {
        port = 60004;
        s.setValue(CONNECTION_PORT, port);
        qDebug() << "No post configured using default " << port;
    }

    ui->portLineEdit->setText(QString::number(port));

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}


void SettingsDialog::accept() {

    QString settingFileName;

    settingFileName.append(CLIENT_SETTINGS_FILE_NAME);

    QSettings s(settingFileName, QSettings::NativeFormat);

    QString host = ui->ipLineEdit->text();
    s.setValue(CONNECTION_HOST, host);


    quint16 port = ui->portLineEdit->text().toInt();
    s.setValue(CONNECTION_PORT, port);


    this->loginWindow->loadSettings();
    close();

    qDebug() << "Accepted";
}

