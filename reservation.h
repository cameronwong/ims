#ifndef RESERVATION_H
#define RESERVATION_H

#include <QtGlobal>
#include <QString>
#include "qdatetimespan.h"
#include "qmoney.h"

class Reservation
{
public:
    Reservation();
    Reservation(quint32 itemID, QDateTimeSpan &timePeriod, QMoney price, quint8 paymentMethod = 0,
                quint8 location = 0, quint16 employeeID = 0, quint32 customerID = 0);

    // CONST MEMBER FUNCTIONS
    quint32 getID() const;
    quint32 getCustomerID() const;
    quint8 getPaymentMethod() const;
    quint32 getItemID() const;
    QDateTimeSpan getTimePeriod() const;
    QMoney getPrice() const;
    quint8 getLocation() const;
    quint16 getEmployeeID() const;

    // MUTATORS
    void changePaymentMethod(quint8 newMethod);
    void changeItemID(quint32 newItemID);
    void changeTimePeriod(QDateTimeSpan newTimePeriod);
    void changePrice(QMoney newPrice);
    void changeLocation(quint8 newLocation);
    void changeEmployeeID(quint16 newEmployeeID);
    void setCustomerID(quint32 cusID);

private:
    quint32 _myID;
    quint32 _customerID;
    quint8 _paymentMethod;
    quint32 _itemID;
    QDateTimeSpan _timePeriod;
    QMoney _price;
    quint8 _location;
    quint16 _employeeID;

    static quint32 _currID;
};

#endif // RESERVATION_H
