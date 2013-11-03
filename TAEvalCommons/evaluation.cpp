#include "evaluation.h"
#include <QDebug>

Evaluation::Evaluation(QObject *parent) :
    QObject(parent),
    id(-1),
    taskSet(false),
    task(NULL)
{
}


/**
 * @brief Evaluation::getRatingString to get the String value of
 *        the current rating.
 * @return String value of the current rating
 */
QString Evaluation::getRatingString()
{
    return ratingForEnum(getRating());
}

/**
 * @brief Evaluation::ratingForEnum
 * @param rate the rating that will be converted to String
 * @return String value of the rating value
 */
QString Evaluation::ratingForEnum(RATING::rating_t rate)
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



void Evaluation::setRating(RATING::rating_t rate) {
    rating = rate;
}


void Evaluation::setRating(quint8 rate) {
    rating = RATING::rating_t(rate);
}

void Evaluation::setRating(QString rate) {
    if (rate.compare("None") == 0) {
        setRating(0);
    } else if (rate.compare("Poor") == 0) {
        setRating(1);
    } else if (rate.compare("Fair") == 0) {
        setRating(2);
    } else if (rate.compare("Good") == 0) {
        setRating(3);
    } else if (rate.compare("Very Good") == 0) {
        setRating(4);
    } else if (rate.compare("Excellent") == 0) {
        setRating(5);
    }
}


QDataStream &operator <<(QDataStream &stream, Evaluation &evaluation) {
    stream << evaluation.getIdString();
    QString rateStr = evaluation.getRatingString();
    stream << rateStr;
    stream << evaluation.getComment();
    qDebug() << "IS THIS EVEN HAPPEENING " << evaluation.getIdString() << evaluation.getRating() << evaluation.getComment();

    if (evaluation.hasTask()) {
        Task* task = evaluation.getTask();
        if (task != NULL) {
            stream << QString("true");
            stream << *task;
        } else {
            stream << QString("false");
        }
    } else {
        stream << QString("false");
    }


    return stream;
}


QDataStream &operator >>(QDataStream &stream, Evaluation &evaluation) {
    QString comment;
    QString aId;
    QString rate;
    QString hasTask;

    stream >> aId;
    qDebug() << aId;
    evaluation.setId(aId.toUInt());

    stream >> rate;
    qDebug() << rate;
    evaluation.setRating(rate);

    stream >> comment;
    qDebug() << comment;
    evaluation.setComment(comment);

    stream >> hasTask;
    qDebug() << hasTask;
    if (hasTask.compare(QString("true")) == 0) {
        Task* task = new Task();
        stream >> *task;
        evaluation.setTask(task);
    }

    return stream;
}




