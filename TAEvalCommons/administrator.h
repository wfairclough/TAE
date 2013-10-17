#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QObject>
#include <QMap>

#include <user.h>
#include <persistable.h>

#define ADMINISTRATOR_TABLE_NAME "ADMINISTRATOR"

class Administrator : public QObject, public User, public Persistable
{
    Q_OBJECT
    Q_ENUMS(user_t)
public:
    explicit Administrator(QObject *parent = 0);

    /**
     * Description: Constructor for building a basic TeachingAssistant isntance
     * Paramters: firstName, lastName, and username
     * Returns: instance of TeachingAssistant
     */
    Administrator(QString fName, QString lName, QString uName);

    user_t type() { return ADMINISTRATOR; }


    // Persistable
    QString getTableName() { return ADMINISTRATOR_TABLE_NAME; }

    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }


signals:
    
public slots:
    
};

#endif // ADMINISTRATOR_H
