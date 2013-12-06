#ifndef TAWINDOW_H
#define TAWINDOW_H

#include <QMainWindow>
#include <teachingassistant.h>
#include <task.h>
#include <course.h>
#include "abstractsubscriber.h"

namespace Ui {
class TaWindow;
}

class TaWindow : public QMainWindow, public AbstractSubscriber
{
    Q_OBJECT
    
public:
    explicit TaWindow(TeachingAssistant* user, QWidget *parent = 0);
    ~TaWindow();
    
    void updateTaskListForTa(QList<Task*> list);
    // ADD remaining calls to abstract subsciber here //


private:
    Ui::TaWindow *ui;
    TeachingAssistant* teachingAssistant;
};

#endif // TAWINDOW_H
