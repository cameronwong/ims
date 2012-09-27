#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    v = new View();
    m = new Model();

    v->show();

    connect(v->getItemView(), SIGNAL(refreshData()), this, SLOT(refreshItemViewData()));
    v->getItemView()->initializeData();
    v->getCustomerView()->initializeData();
    v->getReservationView()->initializeData();
}

Controller::~Controller()
{
    delete v;
    delete m;
}

void Controller::refreshItemViewData()
{
    QMap<quint32, Item> data = m->getItemData();
    v->getItemView()->loadData(data);
}

void Controller::refreshBookResViewItemList()
{
    QMap<quint32, Item> data = m->getItemData();
    QStringList itemNames;

    QMap<quint32, Item>::const_iterator i = data.constBegin();
     while (i != data.constEnd())
         itemNames << i.value().getName();

     v->getBookReservationView()->loadItemList(itemNames);
}
