#ifndef TAMANAGER_H
#define TAMANAGER_H

#include <QObject>
#include <QList>

#include <instructor.h>
#include <teachingassistant.h>
#include <course.h>
#include <task.h>
#include <evaluation.h>

class TaManager : public QObject
{
    Q_OBJECT
public:
    explicit TaManager(QObject *parent = 0);


signals:

public slots:

};

#endif // TAMANAGER_H
