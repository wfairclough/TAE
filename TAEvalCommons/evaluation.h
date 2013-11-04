#ifndef EVALUATION_H
#define EVALUATION_H

#include <QObject>
#include <QMap>

#include <task.h>
#include <persistable.h>

#define EVALUATION_TABLE_NAME "EVALUATION"

namespace RATING {
    enum rating_t {
        NONE = 0,
        POOR,
        FAIR,
        GOOD,
        VERY_GOOD,
        EXCELLENT
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
    void setRating(RATING::rating_t rate);
    void setRating(quint8 rate);
    void setRating(QString rate);
    void setTask(Task* newTask) { task = newTask; taskSet = true; }

    // Getters
    quint32 getId() const { return id; }
    QString getIdString() const { return QString::number(id); }
    QString getComment() const { return comment; }
    RATING::rating_t getRating() const { return rating; }
    QString getRatingString();
    Task* getTask() const { return task; }
    bool hasTask() const { return taskSet; }


    /**
     * @brief Evaluation::ratingForEnum
     * @param rate the rating that will be converted to String
     * @return String value of the rating value
     */
    static QString ratingForEnum(RATING::rating_t rate)
    {
        switch (rate) {
        case RATING::NONE:
        {
            return "None";
            break;
        }
        case RATING::POOR:
        {
            return "Poor";
            break;
        }
        case RATING::FAIR:
        {
            return "Fair";
            break;
        }
        case RATING::GOOD:
        {
            return "Good";
            break;
        }
        case RATING::VERY_GOOD:
        {
            return "Very Good";
            break;
        }
        case RATING::EXCELLENT:
        {
            return "Excellent";
            break;
        }
        default:
            return "";
            break;
        }
    }



    // Persistable
    QString getTableName() { return EVALUATION_TABLE_NAME; }

    QMap<QString, QString> getTuple() { return QMap<QString, QString>(); }

signals:
    
public slots:

private:
    bool taskSet;
    Task* task;
    quint32 id;
    QString comment;
    RATING::rating_t rating;
};

// Operator Override
QDataStream &operator <<(QDataStream &stream, Evaluation &evaluation);
QDataStream &operator >>(QDataStream &stream, Evaluation &evaluation);


#endif // EVALUATION_H
