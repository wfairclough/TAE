#ifndef TEACHINGASSISTANT_H
#define TEACHINGASSISTANT_H

#include <QObject>
#include <user.h>

class TeachingAssistant : public QObject, public User
{
    Q_OBJECT
public:
    explicit TeachingAssistant(QObject *parent = 0);

    /**
     * Description: Constructor for building a basic TeachingAssistant isntance
     * Paramters: id, firstName, lastName, and username
     * Returns: instance of TeachingAssistant
     */
    TeachingAssistant(unsigned long idArg, QString fName, QString lName, QString uName);
    
    user_t type() { return TA; }

signals:
    
public slots:
    
};

#endif // TEACHINGASSISTANT_H
