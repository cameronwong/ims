#include "reservationview.h"

ReservationView::ReservationView(QWidget *parent) :
    QWidget(parent)
{
    resViewLayout = new QVBoxLayout(this);
    resViewLayout->setContentsMargins(0,0,0,0);

    resTable = new QTableWidget(this);
    resTable->setRowCount(10);
    resTable->setColumnCount(6);

    QStringList stringList;
    stringList << "ResID" << "Item" << "Customer" << "Start Date" << "End Date" << "Cost";
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
    QSize s(resTable->horizontalHeader()->length()+120, resTable->verticalHeader()->length()+25);
    return s;
}

void ReservationView::loadData(QList<QStringList> data)
{
    resTable->setRowCount(data.size());

    for(int i=0; i<data.size(); i++)
        for(int j=0; j<resTable->columnCount(); j++)
         resTable->setItem(i, j, newEntry(data[i][j]));

}

QTableWidgetItem * ReservationView::newEntry(QString text)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(text);
    newItem->setTextAlignment(Qt::AlignCenter);
    return newItem;
}
