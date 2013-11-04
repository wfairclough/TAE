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
    return Evaluation::ratingForEnum(getRating());
}




void Evaluation::setRating(RATING::rating_t rate) {
    rating = rate;
}


void Evaluation::setRating(quint8 rate) {
    rating = RATING::rating_t(rate);
}

void Evaluation::setRating(QString rate) {
    rate = rate.toLower();
    if (rate.compare("none") == 0 || rate.compare("0") == 0) {
        setRating(0);
    } else if (rate.compare("poor") == 0 || rate.compare("1") == 0) {
        setRating(1);
    } else if (rate.compare("fair") == 0 || rate.compare("2") == 0) {
        setRating(2);
    } else if (rate.compare("good") == 0 || rate.compare("3") == 0) {
        setRating(3);
    } else if (rate.compare("very good") == 0 || rate.compare("4") == 0) {
        setRating(4);
    } else if (rate.compare("excellent") == 0 || rate.compare("5") == 0) {
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




