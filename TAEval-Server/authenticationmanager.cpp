#include "authenticationmanager.h"

AuthenticationManager::AuthenticationManager(QObject *parent) :
    QObject(parent)
{

}


void AuthenticationManager::validateUserCredentials(QString username, QString password)
{


    emit validatedUserCredentials(true, "TA");
}
