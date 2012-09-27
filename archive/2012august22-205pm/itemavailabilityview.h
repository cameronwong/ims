#ifndef ITEMAVAILABILITYVIEW_H
#define ITEMAVAILABILITYVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QLabel>
#include <QString>

class ItemAvailabilityView : public QWidget
{
    Q_OBJECT
public:
    explicit ItemAvailabilityView(QWidget *parent = 0);
    
    // FROM VIEW
    void setHeader(QString text);
    const QCalendarWidget * getCalendar() const;

signals:
    
public slots:

private:
    QVBoxLayout *viewLayout;
    QLabel *header;
    QCalendarWidget *calendar;

    // we store this because this widget has no window parent
    
};

#endif // ITEMAVAILABILITYVIEW_H
