#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include <QMap>
#include <QDate>

#include <persistable.h>

#define COURSE_TABLE_NAME "COURSE"

class Course : public QObject, public Persistable
{
    Q_OBJECT
    Q_ENUMS(semester_t)
public:

    enum semester_t {
        FALL = 0,
        WINTER,
        SUMMER
    };

    explicit Course(QObject *parent = 0);
    
    // Getter
    semester_t getSemesterType() { return semester; }


    // Persistable
    QString getTableName() { return COURSE_TABLE_NAME; }

    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }
signals:
    
public slots:

private:
    QString name;
    semester_t semester;
    QDate year;

};

#endif // COURSE_H
