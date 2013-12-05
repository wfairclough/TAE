#ifndef ABSTRACTPUBLISHER_H
#define ABSTRACTPUBLISHER_H

#include <QObject>
#include <abstractsubscriber.h>

class AbstractPublisher : public QObject
{
    Q_OBJECT
public:
    explicit AbstractPublisher(QObject *parent = 0);

    virtual void subscribe(AbstractSubscriber* subscriber) = 0;
    virtual bool unsubscribe(AbstractSubscriber* subscriber) = 0;

signals:

public slots:

};

#endif // ABSTRACTPUBLISHER_H
