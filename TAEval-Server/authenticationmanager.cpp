#include "authenticationmanager.h"

AuthenticationManager::AuthenticationManager(QObject *parent) :
    DataAccessManager(parent)
{
}


User* AuthenticationManager::fetchUserForUsername(QString username, SystemError** error)
{

    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT id, firstName, lastName, username, type FROM user WHERE username=?");
    userQuery.addBindValue(username);
    if (userQuery.exec()) {
        while (userQuery.next()) {
            int index = 0;
            int id = userQuery.value(index++).toInt();
            QString firstName = userQuery.value(index++).toString();
            QString lastName = userQuery.value(index++).toString();
            QString usernameValue = userQuery.value(index++).toString();
            User::user_t type = User::user_t(userQuery.value(index++).toInt());


            switch (type) {
            case User::ADMINISTRATOR:
            {
                Administrator* admin = new Administrator;
                admin->setId(id);
                admin->setFirstName(firstName);
                admin->setLastName(lastName);
                admin->setUsername(username);

                return admin;
            }
            case User::INSTRUCTOR:
            {
                Instructor* instructor = new Instructor;
                instructor->setId(id);
                instructor->setFirstName(firstName);
                instructor->setLastName(lastName);
                instructor->setUsername(username);

                return instructor;
            }
            case User::TA:
            {
                TeachingAssistant* ta = new TeachingAssistant;
                ta->setId(id);
                ta->setFirstName(firstName);
                ta->setLastName(lastName);
                ta->setUsername(username);

                return ta;
            }
            default:
                break;
            }
        }
    }

    *error = new SystemError("User not found in system.");

    return NULL;
}
