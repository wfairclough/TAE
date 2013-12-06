#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <administrator.h>


namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(Administrator* user, QWidget *parent = 0);
    ~AdminWindow();

private:
    Ui::AdminWindow *ui;
    Administrator* administrator;

};

#endif // ADMINWINDOW_H
