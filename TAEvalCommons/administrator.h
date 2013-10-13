#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QObject>
#include <user.h>

class Administrator : public QObject, public User
{
    Q_OBJECT
    Q_ENUMS(user_t)
public:
    explicit Administrator(QObject *parent = 0);

    /**
     * Description: Constructor for building a basic TeachingAssistant isntance
     * Paramters: id, firstName, lastName, and username
     * Returns: instance of TeachingAssistant
     */
    Administrator(unsigned long idArg, QString fName, QString lName, QString uName);

    user_t type() { return ADMINISTRATOR; }

signals:
    
public slots:
    
};

#endif // ADMINISTRATOR_H
