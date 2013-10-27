#ifndef APIWINDOW_H
#define APIWINDOW_H

#include <QMainWindow>

namespace Ui {
class ApiWindow;
}

class ApiWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApiWindow(QWidget *parent = 0);
    ~ApiWindow();

private slots:
    void updateStackIndex(int);

private:
    Ui::ApiWindow *ui;
};

#endif // APIWINDOW_H
