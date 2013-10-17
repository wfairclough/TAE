#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include <QDate>

class Course : public QObject
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

signals:
    
public slots:

private:
    QString name;
    semester_t semester;
    QDate year;

};

#endif // COURSE_H
