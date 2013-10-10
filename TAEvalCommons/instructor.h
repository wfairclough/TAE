#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QObject>
#include <user.h>

class Instructor : public QObject, public User
{
    Q_OBJECT
public:
    explicit Instructor(QObject *parent = 0);
    
    user_t type() { return INSTRUCTOR; }

signals:
    
public slots:
    
};

#endif // INSTRUCTOR_H
