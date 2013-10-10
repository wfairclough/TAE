#ifndef USER_H
#define USER_H

#include <QString>
#include <TAEvalCommons_global.h>


class User
{

public:

    virtual user_t type() = 0;

    // Setters
    void setId(unsigned long idArg) { id = idArg; }
    void setFirstName(QString fName) { firstName = fName; }
    void setLastName(QString lName) { lastName = lName; }
    void setUsername(QString uName) { username = uName; }

    // Getters
    unsigned long getId() { return id; }
    QString getFirstName() { return firstName; }
    QString getLastName() { return lastName; }
    QString getUsername() { return username; }
    
protected:
    unsigned long id;
    QString firstName;
    QString lastName;
    QString username;


};

#endif // USER_H
