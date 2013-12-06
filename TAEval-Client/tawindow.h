#ifndef TAWINDOW_H
#define TAWINDOW_H

#include <QMainWindow>
#include <teachingassistant.h>
#include <task.h>
#include <course.h>

namespace Ui {
class TaWindow;
}

class TaWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TaWindow(TeachingAssistant* ta, QWidget *parent = 0);
    ~TaWindow();
    
private:
    Ui::TaWindow *ui;
    TeachingAssistant* teachingAssistant;
};

#endif // TAWINDOW_H
