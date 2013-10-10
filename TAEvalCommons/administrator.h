#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QObject>
#include <user.h>

class Administrator : public QObject, public User
{
    Q_OBJECT
public:
    explicit Administrator(QObject *parent = 0);
    
    user_t type() { return ADMINISTRATOR; }

signals:
    
public slots:
    
};

#endif // ADMINISTRATOR_H
