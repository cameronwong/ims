#include "itemavailabilityview.h"

ItemAvailabilityView::ItemAvailabilityView(QWidget *parent) :
    QWidget(parent)
{
    // create
    viewLayout = new QVBoxLayout(this);
    header = new QLabel(tr("Item Availability"), this);
    calendar = new QCalendarWidget(this);

    // layout
    viewLayout->addWidget(header);
    viewLayout->addWidget(calendar);

    // initialize
    header->setAlignment(Qt::AlignCenter);
    setWindowTitle(tr("Select Reservation Date"));
    setFixedSize(sizeHint());
}

void ItemAvailabilityView::setHeader(QString text)
{
    header->setText(text.prepend("<b>"));
}

const QCalendarWidget * ItemAvailabilityView::getCalendar() const
{
    return calendar;
}
