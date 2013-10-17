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



//QDataStream &operator <<(QDataStream &stream, const TeachingAssistant &user)
//{

//    stream << user;

//    return stream;
//}

//QDataStream &operator >>(QDataStream &stream, TeachingAssistant &user)
//{

//    stream >> super;


//    return stream;
//}
