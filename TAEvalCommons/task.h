#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QMap>

#include <persistable.h>
#include <teachingassistant.h>


#define TASK_TABLE_NAME "TASK"

class Task : public QObject, public Persistable
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

    void setId(quint32 aId) { id = aId; }
    void setName(QString tName) { name = tName; }
    void setDescription(QString desc) { description = desc; }
    quint32 getId() const { return id; }
    QString getName() const { return name; }
    QString getDescription() const { return description; }

    void setTeachingAssistant(TeachingAssistant* ta) { teachingAssistant = ta; }


    // Persistable
    QString getTableName() { return TASK_TABLE_NAME; }

    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }


signals:
    
public slots:
    
private:
    quint32 id;
    QString name;
    QString description;
    TeachingAssistant* teachingAssistant;


};

// Operator Override
QDataStream &operator <<(QDataStream &stream, const Task &user);
QDataStream &operator >>(QDataStream &stream, Task &user);

#endif // TASK_H
