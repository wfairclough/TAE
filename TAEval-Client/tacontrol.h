#ifndef TACONTROL_H
#define TACONTROL_H

#include <QObject>

class TaControl : public QObject
{
    Q_OBJECT
public:
    explicit TaControl(QObject *parent = 0);
    void getTas(QString view);
    void getTaskListForTa(QString view, QString uname);
signals:
    
public slots:
    
};

#endif // TACONTROL_H
