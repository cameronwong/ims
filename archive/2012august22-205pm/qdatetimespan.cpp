#include "qdatetimespan.h"

QDateTimeSpan::QDateTimeSpan()
{
    _startTime = QDateTime::currentDateTime();
    _endTime = QDateTime::currentDateTime();
    _endTime.addDays(2);
}

QDateTimeSpan::QDateTimeSpan(QDateTime startTime, QDateTime endTime)
{
    _startTime = startTime;
    _endTime = endTime;
}

bool QDateTimeSpan::isNow() const
{

    QDateTime now = QDateTime::currentDateTime();

    if(now > _startTime && now < _endTime)
        return true;
    else
        return false;
}

QDateTime QDateTimeSpan::getStartTime() const
{
    return _startTime;
}

QDateTime QDateTimeSpan::getEndTime() const
{
    return _endTime;
}
