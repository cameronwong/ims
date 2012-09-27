#include "model.h"

Model::Model(QObject *parent) :
    QObject(parent)
{
    // create
    customerMap = QMap<quint32, Customer>();
    itemMap = QMap<quint32, Item>();
    resMap = QMap<quint32, Reservation>();

    // debug
    Item newItem1("Streetbike 1");
    Item newItem2("Streetbike 2");
    Item newItem3("Streetbike 3");
    Item newItem4("Chopper 1");
    Item newItem5("Chopper 2");
    Item newItem6("Chopper 3");
    Item newItem7("Golf Cart 1");
    Item newItem8("Golf Cart 2");
    Item newItem9("BMW 1");
    Item newItem10("BMW 2");
    itemMap.insert(newItem1.getID(), newItem1);
    itemMap.insert(newItem2.getID(), newItem2);
    itemMap.insert(newItem3.getID(), newItem3);
    itemMap.insert(newItem4.getID(), newItem4);
    itemMap.insert(newItem5.getID(), newItem5);
    itemMap.insert(newItem6.getID(), newItem6);
    itemMap.insert(newItem7.getID(), newItem7);
    itemMap.insert(newItem8.getID(), newItem8);
    itemMap.insert(newItem9.getID(), newItem9);
    itemMap.insert(newItem10.getID(), newItem10);
}

quint32 Model::addReservation(quint32 &itemID, QDateTimeSpan &timePeriod, QMoney &price, quint8 &paymentMethod,
                           quint8 &location, quint16 &employeeID, quint32 customerID)
{
    Reservation newRes(itemID, timePeriod, price, paymentMethod, location, employeeID, customerID);
    quint32 resID = newRes.getID();
    resMap.insert(resID, newRes);

    emit reservationModelChanged();
    return resID;
}

quint32 Model::addCustomer(QString &firstName, QString &lastName, QString &phoneNumber, QString &email)
{
    Customer newCus(firstName, lastName, phoneNumber, email);
    quint32 cusID = newCus.getID();
    customerMap.insert(cusID, newCus);

    emit customerModelChanged();
    return newCus.getID();
}

void Model::setRelations(quint32 resID, quint32 cusID, quint32 itemID)
{
    if(!customerMap.contains(cusID))
    {
        qDebug() << "ERROR: Model::setRelations [cusID not in database.]";
        return;
    }

    if(!resMap.contains(resID))
    {
        qDebug() << "ERROR: Model::setRelations [resID not in database.]";
        return;
    }

    if(!itemMap.contains(itemID))
    {
        qDebug() << "ERROR: Model::setRelations [itemID not in database.]";
        return;
    }

    resMap[resID].setCustomerID(cusID);
    itemMap[itemID].addBooking(resID);
    customerMap[cusID].addReservation(resID);
}

const QMap<quint32, Item> Model::getItemData() const
{
    return itemMap;
}

const QMap<quint32, Customer> Model::getCustomerData() const
{
    return customerMap;
}

const QMap<quint32, Reservation> Model::getReservationData() const
{
    return resMap;
}

void Model::test()
{
    QMap<quint32, Item>::const_iterator i = itemMap.constBegin();
     while (i != itemMap.constEnd())
     {
         qDebug() << i.key() << ": " << i.value().getName() << "itemID: " << i.value().getID();
         ++i;
     }
}
