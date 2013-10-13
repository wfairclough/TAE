#include "administrator.h"

Administrator::Administrator(QObject *parent) :
    QObject(parent)
{
}


Administrator::Administrator(unsigned long idArg, QString fName, QString lName, QString uName)
{
    setId(idArg);
    setFirstName(fName);
    setLastName(lName);
    setUsername(uName);
}
