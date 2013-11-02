#include "evaluation.h"

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
    case RATING::EXECELLENT:
    {
        return "Execellent";
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


QDataStream &operator <<(QDataStream &stream, const Evaluation &evaluation) {
    stream << evaluation.getIdString();
    stream << evaluation.getRating();
    stream << evaluation.getComment();

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
    evaluation.setId(aId.toUInt());

    stream >> rate;
    evaluation.setRating(rate.toUInt());

    stream >> comment;
    evaluation.setComment(comment);

    stream >> hasTask;
    if (hasTask.compare(QString("true")) == 0) {
        Task* task = new Task();
        stream >> *task;
        evaluation.setTask(task);
    }

    return stream;
}




