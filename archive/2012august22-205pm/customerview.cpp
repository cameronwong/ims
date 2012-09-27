#include "customerview.h"

CustomerView::CustomerView(QWidget *parent) :
    QWidget(parent)
{
    // create
    customerLayout = new QVBoxLayout(this);
    customerTable = new QTableWidget(this);

    // layout
    customerLayout->addWidget(customerTable);

    // initialize
    customerTable->setRowCount(10);
    customerTable->setColumnCount(5);

    QStringList stringList;
    stringList << "First Name" << "Last Name" << "Email" << "Phone" << "# Res";
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
    QSize s(customerTable->horizontalHeader()->length()+120, customerTable->verticalHeader()->length()+50);
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
         customerTable->setItem(row, 2, newEntry(i.value().getEmail()));
         customerTable->setItem(row, 3, newEntry(i.value().getPhoneNumber()));
         customerTable->setItem(row, 4, newEntry(QString::number(i.value().getResCount())));

         ++row;
         ++i;
     }
}

QTableWidgetItem * CustomerView::newEntry(QString text)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(text);
    newItem->setTextAlignment(Qt::AlignCenter);
    return newItem;
}
