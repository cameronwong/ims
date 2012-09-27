#include "itemview.h"

ItemView::ItemView(QWidget *parent) :
    QWidget(parent)
{
    itemViewLayout = new QVBoxLayout(this);
    itemTable = new QTableWidget(this);

    itemViewLayout->addWidget(itemTable);

    itemTable->setRowCount(10);
    itemTable->setColumnCount(4);

    QStringList stringList;
    stringList << "Name" << "ID" << "Status" << "Date Added";
    itemTable->setHorizontalHeaderLabels(stringList);
    itemTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    itemTable->setSelectionMode(QAbstractItemView::SingleSelection);
    itemTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    itemTable->horizontalHeader()->setStretchLastSection(true);
    itemTable->setSortingEnabled(true);

    // connections
    connect(itemTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(itemSelected(int)));
}

void ItemView::initializeData()
{
    emit refreshData();
}

void ItemView::itemSelected(int row)
{
    emit itemAvailRequested(itemTable->item(row,0)->text(), row);
}

void ItemView::launchBookReservation(QDate date)
{
    BookReservationView * b;
    b = new BookReservationView();
    b->setDate(date);
    b->show();
}

QSize ItemView::sizeHint() const
{
    QSize s(itemTable->horizontalHeader()->length()+120, itemTable->verticalHeader()->length()+50);
    return s;
}

void ItemView::loadData(QMap<quint32, Item> data)
{
    itemTable->setRowCount(data.size());
    quint32 row = 0;

    QMap<quint32, Item>::const_iterator i = data.constBegin();
     while (i != data.constEnd())
     {
         itemTable->setItem(row, 0, newEntry(i.value().getName()));
         itemTable->setItem(row, 1, newEntry(QString::number(i.value().getID())));
         itemTable->setItem(row, 2, newEntry(i.value().availableText()));
         itemTable->setItem(row, 3, newEntry(i.value().getDateAdded().toString(Qt::SystemLocaleShortDate)));

         ++row;
         ++i;
     }

//    itemTable->resizeColumnsToContents();
}

QTableWidgetItem * ItemView::newEntry(QString text)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(text);
    newItem->setTextAlignment(Qt::AlignCenter);
    return newItem;
}
