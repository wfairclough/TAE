#include "systemerror.h"

SystemError::SystemError(QString errMsg, QObject *parent) :
    errorMessage(errMsg),
    QObject(parent)
{
}
