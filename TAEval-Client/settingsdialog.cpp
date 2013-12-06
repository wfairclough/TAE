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

    QRegExp portRegExp("\\d{1,6}");
    QRegExp ipRegExp("\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");

    ui->portLineEdit->setValidator(new QRegExpValidator(portRegExp, this));
    ui->ipLineEdit->setValidator(new QRegExpValidator(ipRegExp, this));


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


/**
 * Description: Slot triggered by IP field when finished editing
 * Paramters: None
 * Returns: void
 */
void SettingsDialog::on_ipLineEdit_lostFocus()
{
    if (ui->ipLineEdit->hasAcceptableInput() || (ui->ipLineEdit->text().compare(QString("localhost")) == 0)) {
        QString lineEditStyle("QLineEdit {}");
        ui->ipLineEdit->setStyleSheet(lineEditStyle);
    } else {
        QString lineEditStyle("QLineEdit {background: #FF8584; color: white;}");
        ui->ipLineEdit->setStyleSheet(lineEditStyle);
    }
}


/**
 * Description: Slot triggered by port field when finished editing
 * Paramters: None
 * Returns: void
 */
void SettingsDialog::on_portLineEdit_lostFocus()
{
    if (ui->portLineEdit->hasAcceptableInput()) {
        QString lineEditStyle("QLineEdit {}");
        ui->portLineEdit->setStyleSheet(lineEditStyle);
    } else {
        QString lineEditStyle("QLineEdit {background: #FF8584; color: white;}");
        ui->portLineEdit->setStyleSheet(lineEditStyle);
    }
}


/**
 * @brief SettingsDialog::accept Triggered when ok button is pressed
 */
void SettingsDialog::accept() {

    if (!ui->portLineEdit->hasAcceptableInput()) {
        return;
    }

    if (!ui->ipLineEdit->hasAcceptableInput() && (ui->ipLineEdit->text().compare(QString("localhost")) != 0)) {
        return;
    }

    QString settingFileName;

    settingFileName.append(CLIENT_SETTINGS_FILE_NAME);

    QSettings s(settingFileName, QSettings::NativeFormat);

    QString host = ui->ipLineEdit->text();
    s.setValue(CONNECTION_HOST, host);


    quint16 port = ui->portLineEdit->text().toInt();
    s.setValue(CONNECTION_PORT, port);

    // Reload settings on login Window
    this->loginWindow->loadSettings();
    close();
}



