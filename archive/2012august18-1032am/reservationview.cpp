#include "reservationview.h"

ReservationView::ReservationView(QWidget *parent) :
    QWidget(parent)
{
    resViewLayout = new QVBoxLayout(this);

    resTable = new QTableWidget(this);
    resTable->setRowCount(10);
    resTable->setColumnCount(5);

    QStringList stringList;
    stringList << "ResID" << "Item" << "Customer" << "Start Date" << "End Date";
    resTable->setHorizontalHeaderLabels(stringList);
    resTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    resTable->setSelectionMode(QAbstractItemView::SingleSelection);
    resTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resTable->horizontalHeader()->setStretchLastSection(true);
    resTable->setSortingEnabled(true);

    resViewLayout->addWidget(resTable);
}

void ReservationView::initializeData()
{
    emit refreshData();
}

QSize ReservationView::sizeHint() const
{
    QSize s(resTable->horizontalHeader()->length()+120, resTable->verticalHeader()->length()+50);
    return s;
}

void ReservationView::loadData(QMap<quint32, Reservation> data)
{
    resTable->setRowCount(data.size());
    quint32 row = 0;

    QMap<quint32, Reservation>::const_iterator i = data.constBegin();
     while (i != data.constEnd())
     {
         resTable->setItem(row, 0, newEntry(QString::number(i.value().getID())));
         resTable->setItem(row, 1, newEntry(QString::number(i.value().getItemID())));
         resTable->setItem(row, 2, newEntry(QString::number(i.value().getCustomerID())));
         resTable->setItem(row, 3, newEntry(i.value().getTimePeriod().getStartTime().toString(Qt::SystemLocaleShortDate)));
         resTable->setItem(row, 4, newEntry(i.value().getTimePeriod().getEndTime().toString(Qt::SystemLocaleShortDate)));

         ++row;
         ++i;
     }
}

QTableWidgetItem * ReservationView::newEntry(QString text)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(text);
    newItem->setTextAlignment(Qt::AlignCenter);
    return newItem;
}
