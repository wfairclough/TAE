#ifndef INSTRUCTORWINDOW_H
#define INSTRUCTORWINDOW_H

#include <QMainWindow>
#include <instructor.h>
#include <course.h>
#include <task.h>
#include <evaluation.h>

namespace Ui {
class InstructorWindow;
}

class InstructorWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit InstructorWindow(Instructor* user, QWidget *parent = 0);
    ~InstructorWindow();
    
private:
    Ui::InstructorWindow *ui;
    Instructor* instructor;
};

#endif // INSTRUCTORWINDOW_H
