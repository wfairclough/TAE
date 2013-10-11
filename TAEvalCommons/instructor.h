#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QObject>
#include <user.h>

class Instructor : public QObject, public User
{
    Q_OBJECT
public:
    explicit Instructor(QObject *parent = 0);
    
    /**
     * Description: Constructor for building a basic TeachingAssistant isntance
     * Paramters: id, firstName, lastName, and username
     * Returns: instance of TeachingAssistant
     */
    Instructor(unsigned long idArg, QString fName, QString lName, QString uName);


    user_t type() { return INSTRUCTOR; }


signals:
    
public slots:
    
};

// Operator Override
QDataStream &operator <<(QDataStream &stream, const Instructor &user);
QDataStream &operator >>(QDataStream &stream, Instructor &user);

#endif // INSTRUCTOR_H
