#ifndef APICONTROL_H
#define APICONTROL_H

#include <QObject>
#include <instructor.h>


class InstructorControl : public QObject
{
    Q_OBJECT
public:
    explicit InstructorControl(QObject *parent = 0);
    void getTaForInstructor(QString view, QString uname);
    void getInstructors(QString view);
    void getCoursesForInstructor(QString view, QString uname);
    
signals:
    
public slots:

private:

    
};

#endif // APICONTROL_H
