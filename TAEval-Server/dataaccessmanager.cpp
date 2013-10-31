#include "dataaccessmanager.h"

DataAccessManager::DataAccessManager(QObject *parent) :
    QObject(parent)
{

}


/**
 * @brief idForUsername get the userId for a username.
 *        Returns -1 if not found.
 * @param username
 * @return
 */
int DataAccessManager::idForUsername(QString username) {
    QSqlDatabase db = DbCoordinator::getInstance().getDatabase();

    int id = -1;

    QSqlQuery allTaQuery(db);
    allTaQuery.prepare("SELECT id FROM user WHERE username=?");
    allTaQuery.addBindValue(username);
    if(allTaQuery.exec()) {
        while(allTaQuery.next()) {
            id = allTaQuery.value(0).toInt();

        }
    }

    return id;
}
