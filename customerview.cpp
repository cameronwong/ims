#include "customerview.h"

CustomerView::CustomerView(QWidget *parent) :
    QWidget(parent)
{
    // create
    customerLayout = new QVBoxLayout(this);
    customerTable = new QTableWidget(this);

    // layout
    customerLayout->addWidget(customerTable);
    customerLayout->setContentsMargins(0,0,0,0);

    // initialize
    customerTable->setRowCount(10);
    customerTable->setColumnCount(5);

    QStringList stringList;
    stringList << "First Name" << "Last Name" << "# Res" << "Email" << "Phone";
    customerTable->setHorizontalHeaderLabels(stringList);
    customerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    customerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    customerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    customerTable->horizontalHeader()->setStretchLastSection(true);
    customerTable->setSortingEnabled(true);

    // debug
}

void CustomerView::initializeData()
{
    emit refreshData();
}

QSize CustomerView::sizeHint() const
{
    QSize s(customerTable->horizontalHeader()->length()+120, customerTable->verticalHeader()->length()+25);
    return s;
}

void CustomerView::loadData(QMap<quint32, Customer> data)
{
    customerTable->setRowCount(data.size());
    quint32 row = 0;

    QMap<quint32, Customer>::const_iterator i = data.constBegin();
     while (i != data.constEnd())
     {
         customerTable->setItem(row, 0, newEntry(i.value().getFirstName()));
         customerTable->setItem(row, 1, newEntry(i.value().getLastName()));
         customerTable->setItem(row, 2, newEntry(QString::number(i.value().getResCount())));
         customerTable->setItem(row, 3, newEntry(i.value().getEmail()));
         customerTable->setItem(row, 4, newEntry(i.value().getPhoneNumber()));

         ++row;
         ++i;
     }

    customerTable->resizeColumnToContents(0);
    customerTable->resizeColumnToContents(1);
    customerTable->resizeColumnToContents(3);
    customerTable->resizeColumnToContents(4);
}

QTableWidgetItem * CustomerView::newEntry(QString text)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(text);
    newItem->setTextAlignment(Qt::AlignCenter);
    return newItem;
}
