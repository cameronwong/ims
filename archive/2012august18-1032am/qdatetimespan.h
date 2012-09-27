#ifndef QDATETIMESPAN_H
#define QDATETIMESPAN_H

#include <QDateTime>

class QDateTimeSpan
{
public:
    QDateTimeSpan();
    QDateTimeSpan(QDateTime startTime, QDateTime endTime);

    bool isNow() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;

private:
    QDateTime _startTime;
    QDateTime _endTime;

};

#endif // QDATETIMESPAN_H
