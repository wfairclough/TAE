#include "teachingassistant.h"

TeachingAssistant::TeachingAssistant(QObject *parent) :
    QObject(parent)
{
}

TeachingAssistant::TeachingAssistant(QString fName, QString lName, QString uName)
{
    setFirstName(fName);
    setLastName(lName);
    setUsername(uName);
}

