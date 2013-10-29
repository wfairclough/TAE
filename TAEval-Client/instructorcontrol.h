#ifndef APICONTROL_H
#define APICONTROL_H

#include <QObject>
#include "instructor.h"

class InstructorControl : public QObject
{
    Q_OBJECT
public:
    explicit InstructorControl(QObject *parent = 0);
    void getTaForInstructor(QString uname);
    void getInstructors();
    
signals:
    
public slots:

private:

    
};

#endif // APICONTROL_H
