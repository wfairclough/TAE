#include "teachingassistant.h"

TeachingAssistant::TeachingAssistant(QObject *parent) :
    QObject(parent)
{
}

TeachingAssistant::TeachingAssistant(unsigned long idArg, QString fName, QString lName, QString uName)
{
    setId(idArg);
    setFirstName(fName);
    setLastName(lName);
    setUsername(uName);
}
