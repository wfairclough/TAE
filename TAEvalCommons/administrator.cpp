#include "administrator.h"

Administrator::Administrator(QObject *parent) :
    QObject(parent)
{
}


Administrator::Administrator(QString fName, QString lName, QString uName)
{
    setFirstName(fName);
    setLastName(lName);
    setUsername(uName);
}
