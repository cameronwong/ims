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
    QMap<quint32, Item> data = m->getItemData();
    v->getItemView()->loadData(data);
}

void Controller::refreshCustomerViewData()
{
    QMap<quint32, Customer> data = m->getCustomerData();
    v->getCustomerView()->loadData(data);
}

void Controller::refreshReservationViewData()
{
    QMap<quint32, Reservation> data = m->getReservationData();
    v->getReservationView()->loadData(data);
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
    quint32 cusID = m->addCustomer(firstName, lastName, phoneNumber, email);
    m->setRelations(resID, cusID, itemID);

    // DEBUG
    qDebug() << "itemID = " << itemID;
    qDebug() << "dollars = " << dollars;
    qDebug() << "cents = " << cents;
    qDebug() << "paymentMethod = " << paymentMethod;
    qDebug() << "location = " << location;
    qDebug() << "employeeID = " << employeeID;

}
