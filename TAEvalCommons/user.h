#ifndef USER_H
#define USER_H

#include <QString>
#include <TAEvalCommons_global.h>

class User {

public:

    enum user_t {
        NONE = 0,
        ADMINISTRATOR,
        INSTRUCTOR,
        TA
    };

    virtual user_t type() = 0;

    // Setters
    void setFirstName(QString fName) { firstName = fName; }
    void setLastName(QString lName) { lastName = lName; }
    void setUsername(QString uName) { username = uName; }

    // Getters
    QString getFirstName() const { return firstName; }
    QString getLastName() const { return lastName; }
    QString getUsername() const { return username; }
    
protected:
    QString firstName;
    QString lastName;
    QString username;


};

// Operator Override
QDataStream &operator <<(QDataStream &stream, const User &user);
QDataStream &operator >>(QDataStream &stream, User &user);


#endif // USER_H
