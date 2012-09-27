#include "itemview.h"

ItemView::ItemView(QWidget *parent) :
    QWidget(parent)
{
    itemViewLayout = new QVBoxLayout(this);
    itemTable = new QTableWidget(this);

    itemViewLayout->addWidget(itemTable);
    itemViewLayout->setContentsMargins(0,0,0,0);

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
    QSize s(itemTable->horizontalHeader()->length()+120, itemTable->verticalHeader()->length()+25);
    return s;
}

void ItemView::loadData(QList<QStringList> data)
{
    itemTable->setRowCount(data.size());

    for(int i=0; i<data.size(); i++)
    {
        if(data[i][2] == "Booked")
            for(int j=0; j<itemTable->columnCount(); j++)
                itemTable->setItem(i, j, newRedEntry(data[i][j]));

        else
            for(int j=0; j<itemTable->columnCount(); j++)
                itemTable->setItem(i, j, newEntry(data[i][j]));
    }

//    itemTable->resizeColumnsToContents();
}

QTableWidgetItem * ItemView::newEntry(QString text)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(text);
    newItem->setTextAlignment(Qt::AlignCenter);
    return newItem;
}

QTableWidgetItem * ItemView::newRedEntry(QString text)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(text);
    newItem->setTextAlignment(Qt::AlignCenter);
    newItem->setBackgroundColor(Qt::red);
    return newItem;
}
