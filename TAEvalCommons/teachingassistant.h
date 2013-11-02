#ifndef TEACHINGASSISTANT_H
#define TEACHINGASSISTANT_H

#include <QObject>
#include <QMap>

#include <user.h>
#include <persistable.h>

#define TEACHING_ASSISTANT_TABLE_NAME "TEACHING_ASSISTANT"

class TeachingAssistant : public QObject, public User, public Persistable
{
    Q_OBJECT
    Q_ENUMS(user_t)
public:
    explicit TeachingAssistant(QObject *parent = 0);

    /**
     * Description: Constructor for building a basic TeachingAssistant isntance
     * Paramters: firstName, lastName, and username
     * Returns: instance of TeachingAssistant
     */
    TeachingAssistant(QString fName, QString lName, QString uName);
    
    user_t type() { return TA; }


    // Persistable
    QString getTableName() { return TEACHING_ASSISTANT_TABLE_NAME; }

    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }


signals:
    
public slots:
    
};

#endif // TEACHINGASSISTANT_H
