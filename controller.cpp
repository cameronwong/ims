#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    v = new View();
    m = new Model();

    v->show();

    connect(v->getItemView(), SIGNAL(refreshData()), this, SLOT(refreshItemViewData()));
    connect(v->getCustomerView(), SIGNAL(refreshData()), this, SLOT(refreshCustomerViewData()));
    connect(v->getReservationView(), SIGNAL(refreshData()), this, SLOT(refreshReservationViewData()));
    connect(v->getBookReservationView(), SIGNAL(sendReservation(QStringList,QList<quint32>,QDateTime,QDateTime)),
            this, SLOT(bookReservation(QStringList,QList<quint32>,QDateTime,QDateTime)));
    connect(v, SIGNAL(clearDatabase()), m, SLOT(nukeDatabase()));

    connect(m, SIGNAL(customerModelChanged()), v->getCustomerView(), SIGNAL(refreshData()));
    connect(m, SIGNAL(itemModelChanged()), v->getItemView(), SIGNAL(refreshData()));
    connect(m, SIGNAL(reservationModelChanged()), v->getReservationView(), SIGNAL(refreshData()));

    v->getItemView()->initializeData();
    v->getCustomerView()->initializeData();
    v->getReservationView()->initializeData();

    refreshBookResViewItemList();
}

Controller::~Controller()
{
    delete v;
    delete m;
}

void Controller::refreshItemViewData()
{
    QMap<quint32, Item> dataIn = m->getItemData();
    QList<QStringList> dataOut;

    QMap<quint32, Item>::const_iterator i = dataIn.constBegin();
     while (i != dataIn.constEnd())
     {
         QStringList itemEntry;

         itemEntry << i.value().getName();
         itemEntry << QString::number(i.value().getID());
         if(m->itemAvailable(i.key(), QDateTimeSpan()))
             itemEntry << tr("Available");
         else
             itemEntry << tr("Booked");
             itemEntry << i.value().getDateAdded().toString(Qt::SystemLocaleShortDate);

         dataOut.append(itemEntry);

         ++i;
     }

    v->getItemView()->loadData(dataOut);
}

void Controller::refreshCustomerViewData()
{
    QMap<quint32, Customer> data = m->getCustomerData();
    v->getCustomerView()->loadData(data);
}

void Controller::refreshReservationViewData()
{
    QMap<quint32, Reservation> dataIn = m->getReservationData();
    QList<QStringList> dataOut;

    QMap<quint32, Reservation>::const_iterator i = dataIn.constBegin();
     while (i != dataIn.constEnd())
     {
         QStringList resEntry;

         resEntry << QString::number(i.value().getID());
         resEntry << m->getItemNamebyID(i.value().getItemID());
         resEntry << m->getCustomerNamebyID(i.value().getCustomerID());
         resEntry << i.value().getTimePeriod().getStartTime().date().toString(Qt::SystemLocaleShortDate);
         resEntry << i.value().getTimePeriod().getEndTime().date().toString(Qt::SystemLocaleShortDate);
         resEntry << i.value().getPrice().toString();

         dataOut.append(resEntry);

         ++i;
     }

    v->getReservationView()->loadData(dataOut);
}

void Controller::refreshBookResViewItemList()
{
    QMap<quint32, Item> data = m->getItemData();
    QStringList itemNames;

    QMap<quint32, Item>::const_iterator i = data.constBegin();
     while (i != data.constEnd())
     {
         itemNames << i.value().getName();
         ++i;
     }

     v->getBookReservationView()->loadItemList(itemNames);
}

void Controller::bookReservation(QStringList textParameters, QList<quint32> numericParameters,
                                 QDateTime startTime, QDateTime endTime)
{
    QDateTimeSpan timePeriod(startTime, endTime);
    QString firstName = textParameters.at(0);
    QString lastName = textParameters.at(1);
    QString email = textParameters.at(2);
    QString phoneNumber = textParameters.at(3);
    QString dollars = textParameters.at(4).section('.', 0, 0);
    QString cents = textParameters.at(4).section('.', 1, 1);
    QMoney cost(dollars.toULong(), cents.toULong());

    quint32 itemID = numericParameters.at(0);
    quint8 location = numericParameters.at(1);
    quint8 paymentMethod = numericParameters.at(2);
    quint16 employeeID = numericParameters.at(3);

    quint32 resID = m->addReservation(itemID, timePeriod, cost, paymentMethod, location, employeeID);

    quint32 cusID = m->getCustomerIDbyName(firstName, lastName);
    if(cusID == (quint32) -1)
        cusID = m->addCustomer(firstName, lastName, phoneNumber, email);
    else
        m->updateCustomerInfo(cusID, phoneNumber, email);

    m->setRelations(resID, cusID, itemID);

    // DEBUG
    qDebug() << "itemID = " << itemID;
    qDebug() << "dollars = " << dollars;
    qDebug() << "cents = " << cents;
    qDebug() << "paymentMethod = " << paymentMethod;
    qDebug() << "location = " << location;
    qDebug() << "employeeID = " << employeeID;

}
