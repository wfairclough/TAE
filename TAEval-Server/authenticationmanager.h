#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include <QObject>

class AuthenticationManager : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationManager(QObject *parent = 0);
    
    void validateUserCredentials(QString username, QString password);


signals:
    void validatedUserCredentials(bool, QString);

public slots:

private:

    
};

#endif // AUTHENTICATIONMANAGER_H
