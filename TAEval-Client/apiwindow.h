#ifndef APIWINDOW_H
#define APIWINDOW_H

#include <QMainWindow>
#include "instructorcontrol.h"
#include "teachingassistant.h"

namespace Ui {
class ApiWindow;
}

class ApiWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApiWindow(QWidget *parent = 0);
    ~ApiWindow();

public slots:
    void recievedTaListForInstructor(QList<TeachingAssistant*> list);

private slots:
    void handleNewTask();
    void handleEditTask();
    void handleDeleteTask();
    void handleAssignTask();
    void handleEvaluateTask();
    void handleViewTa();
    void handleViewCourse();
    void handleViewTask();

private:
    Ui::ApiWindow *ui;
};

#endif // APIWINDOW_H
