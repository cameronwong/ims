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

    // NOTE: THIS PROBABLY DOUBLE UPDATES THE VIEWS.
    // NEED TO OPTIMIZE
    resMap[resID].setCustomerID(cusID);
    emit reservationModelChanged();

    itemMap[itemID].addBooking(resID);
    emit itemModelChanged();

    customerMap[cusID].addReservation(resID);
    emit customerModelChanged();
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

quint32 Model::getCustomerIDbyName(QString &firstName, QString &lastName)
{
    QMap<quint32, Customer>::const_iterator i = customerMap.constBegin();
     while (i != customerMap.constEnd())
     {
         if(i.value().getFirstName() == firstName && i.value().getLastName() == lastName)
             return i.key();
         ++i;
     }

     return -1; //"not found" value
}

QString Model::getCustomerNamebyID(quint32 customerID)
{
    if(customerMap.contains(customerID))
    {
        Customer c = customerMap.value(customerID);
        QString fullName = c.getFirstName();
        fullName.append(" ");
        fullName.append(c.getLastName());

        return fullName;
    }

    return tr("ERROR: CUSTOMER NOT FOUND");
}

void Model::updateCustomerInfo(quint32 cusID, QString &phoneNumber, QString &email)
{
    // already have done a check, this should be in here.
    customerMap[cusID].setPhoneNumber(phoneNumber);
    customerMap[cusID].setEmail(email);

    emit customerModelChanged();
}

bool Model::itemAvailable(quint32 itemID, QDateTimeSpan timeFrame)
{
    if(!itemMap.contains(itemID))
        return false;

    QList<quint32> bookings = itemMap.value(itemID).getBookings();
    for(int i=0; i<bookings.size(); i++)
    {
        quint32 resID = bookings.at(i);
        if(!resMap.contains(resID))
            qDebug() << "ERROR -> Model::itemAvailable [resID does not exist in database]";

        QDateTime startTime = timeFrame.getStartTime();
        QDateTime endTime = timeFrame.getEndTime();

        QDateTimeSpan resTimeFrame = resMap.value(resID).getTimePeriod();
        QDateTime resStartTime = resTimeFrame.getStartTime();
        QDateTime resEndTime = resTimeFrame.getEndTime();

        if(startTime > resStartTime && startTime < resEndTime)
            return false;

        if(endTime > resStartTime && endTime < resEndTime)
            return false;
    }

    return true;
}

QString Model::getItemNamebyID(quint32 itemID)
{
    if(!itemMap.contains(itemID))
        return tr("ERROR: ITEM NOT FOUND");

    return itemMap.value(itemID).getName();
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

void Model::nukeDatabase()
{
    itemMap.clear();
    emit itemModelChanged();

    customerMap.clear();
    emit customerModelChanged();

    resMap.clear();
    emit reservationModelChanged();
}
