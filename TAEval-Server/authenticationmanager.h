#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include <dataaccessmanager.h>
#include <instructor.h>
#include <administrator.h>
#include <teachingassistant.h>
#include <systemerror.h>

class AuthenticationManager : public DataAccessManager
{
    Q_OBJECT
public:
    explicit AuthenticationManager(QObject *parent = 0);

    User* fetchUserForUsername(QString username, SystemError **error);

signals:

public slots:

};

#endif // AUTHENTICATIONMANAGER_H
