#include "evaluation.h"

Evaluation::Evaluation(QObject *parent) :
    QObject(parent)
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
