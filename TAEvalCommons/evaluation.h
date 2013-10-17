#ifndef EVALUATION_H
#define EVALUATION_H

#include <QObject>
#include <QMap>

#include <persistable.h>

#define EVALUATION_TABLE_NAME "EVALUATION"

namespace RATING {
    enum rating_t {
        NONE = 0,
        POOR,
        FAIR,
        GOOD,
        VERY_GOOD,
        EXECELLENT
    };
}

class Evaluation : public QObject, public Persistable
{
    Q_OBJECT

public:
    explicit Evaluation(QObject *parent = 0);

    // Setter
    void setId(quint32 aId) { id = aId; }
    void setComment(QString com) { comment = com; }
    void setComment(RATING::rating_t rate) { rating = rate; }

    // Getters
    quint32 getId() { return id; }
    QString getComment() { return comment; }
    RATING::rating_t getRating() { return rating; }
    QString getRatingString();
    QString ratingForEnum(RATING::rating_t rate);

    // Persistable
    QString getTableName() { return EVALUATION_TABLE_NAME; }

    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }

signals:
    
public slots:

private:
    quint32 id;
    QString comment;
    RATING::rating_t rating;
};

#endif // EVALUATION_H
