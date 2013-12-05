#ifndef INSTRUCTORWINDOW_H
#define INSTRUCTORWINDOW_H

#include <QMainWindow>

namespace Ui {
class InstructorWindow;
}

class InstructorWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit InstructorWindow(QWidget *parent = 0);
    ~InstructorWindow();
    
private:
    Ui::InstructorWindow *ui;
};

#endif // INSTRUCTORWINDOW_H
