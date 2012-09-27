#include "reservation.h"
quint32 Reservation::_currID = 0;

Reservation::Reservation()
{
    _myID = _currID++;
    _customerID = 0;
    _paymentMethod = 0;
    _itemID = 0;
    _timePeriod = QDateTimeSpan();
    _price = QMoney();
    _location = 0;
    _employeeID = 0;
}

Reservation::Reservation(quint32 itemID, QDateTimeSpan &timePeriod, QMoney price, quint8 paymentMethod,
                         quint8 location, quint16 employeeID, quint32 customerID)
{
    _myID = _currID++;
    _customerID = customerID;
    _paymentMethod = paymentMethod;
    _itemID = itemID;
    _timePeriod = timePeriod;
    _price = price;
    _location = location;
    _employeeID = employeeID;
}

quint32 Reservation::getID() const
{
    return _myID;
}

quint32 Reservation::getCustomerID() const
{
    return _customerID;
}

quint8 Reservation::getPaymentMethod() const
{
    return _paymentMethod;
}

quint32 Reservation::getItemID() const
{
    return _itemID;
}

QDateTimeSpan Reservation::getTimePeriod() const
{
    return _timePeriod;
}

QMoney Reservation::getPrice() const
{
    return _price;
}

quint8 Reservation::getLocation() const
{
    return _location;
}

quint16 Reservation::getEmployeeID() const
{
    return _employeeID;
}

void Reservation::changePaymentMethod(quint8 newMethod)
{
    _paymentMethod = newMethod;
}

void Reservation::changeItemID(quint32 newItemID)
{
    _itemID = newItemID;
}

void Reservation::changeTimePeriod(QDateTimeSpan newTimePeriod)
{
    _timePeriod = newTimePeriod;
}

void Reservation::changePrice(QMoney newPrice)
{
    _price = newPrice;
}

void Reservation::changeLocation(quint8 newLocation)
{
    _location = newLocation;
}

void Reservation::changeEmployeeID(quint16 newEmployeeID)
{
    _employeeID = newEmployeeID;
}

void Reservation::setCustomerID(quint32 cusID)
{
    _customerID = cusID;
}
