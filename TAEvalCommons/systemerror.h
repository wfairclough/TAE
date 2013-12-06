#ifndef SYSTEMERROR_H
#define SYSTEMERROR_H

#include <QObject>

/**
 * @brief The SystemError class
 *
 * Simple Wrapper for Error messages in the system
 */
class SystemError : public QObject
{
    Q_OBJECT
public:
    explicit SystemError(QString errMsg, QObject *parent = 0);

    QString getErrorMessage() const { return errorMessage; }

    void setErrorMessage(QString errMsg) { errorMessage = errMsg; }

signals:

public slots:

private:
    QString errorMessage;

};

#endif // SYSTEMERROR_H
