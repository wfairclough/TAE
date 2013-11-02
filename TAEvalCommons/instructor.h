#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QObject>
#include <QMap>

#include <user.h>
#include <persistable.h>

#define INSTRUCTOR_TABLE_NAME "INSTRUCTOR"

class Instructor : public QObject, public User, public Persistable
{
    Q_OBJECT
    Q_ENUMS(user_t)
public:
    explicit Instructor(QObject *parent = 0);
    
    /**
     * Description: Constructor for building a basic TeachingAssistant isntance
     * Paramters: firstName, lastName, and username
     * Returns: instance of TeachingAssistant
     */
    Instructor(QString fName, QString lName, QString uName);


    user_t type() { return INSTRUCTOR; }


    // Persistable
    QString getTableName() { return INSTRUCTOR_TABLE_NAME; }

    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }


signals:
    
public slots:
    
};

// Operator Override
//QDataStream &operator <<(QDataStream &stream, const Instructor &user);
//QDataStream &operator >>(QDataStream &stream, Instructor &user);

#endif // INSTRUCTOR_H
