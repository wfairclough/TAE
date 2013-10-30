#ifndef APICONTROL_H
#define APICONTROL_H

#include <QObject>

class InstructorControl : public QObject
{
    Q_OBJECT
public:
    explicit InstructorControl(QObject *parent = 0);
    void getTaForInstructor(QString view, QString uname);
    void getInstructors(QString view);
    
signals:
    
public slots:

private:

    
};

#endif // APICONTROL_H
