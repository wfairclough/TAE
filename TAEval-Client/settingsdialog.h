#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "loginwindow.h"


namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(LoginWindow *parent = 0);
    ~SettingsDialog();

private slots:
    void accept();

    void on_ipLineEdit_lostFocus();
    void on_portLineEdit_lostFocus();

private:
    Ui::SettingsDialog *ui;
    LoginWindow* loginWindow;


};

#endif // SETTINGSDIALOG_H
