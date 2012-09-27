#include "customer.h"
quint32 Customer::_currID = 0;

Customer::Customer()
{
    _myID = _currID++;
    _firstName = QString("");
    _lastName = QString("");
    _phoneNumber = QString("");
    _email = QString("");
    _resCount = 0;
    _reservations = QList<quint32>();
}

Customer::Customer(QString &firstName, QString lastName, QString phoneNumber, QString email)
{
    _myID = _currID++;
    _firstName = firstName;
    _lastName = lastName;
    _phoneNumber = phoneNumber;
    _email = email;
    _resCount = 0;
    _reservations = QList<quint32>();
}

quint32 Customer::getID() const
{
    return _myID;
}

QString Customer::getFirstName() const
{
    return _firstName;
}

QString Customer::getLastName() const
{
    return _lastName;
}

QString Customer::getName() const
{
    QString result;
    result.append(_firstName);
    result.append(" ");
    result.append(_lastName);

    return result;
}

QString Customer::getPhoneNumber() const
{
    return _phoneNumber;
}

QString Customer::getEmail() const
{
    return _email;
}

quint16 Customer::getResCount() const
{
    return _resCount;
}

QList<quint32> Customer::getReservations() const
{
    return _reservations;
}
void Customer::setName(QString firstName, QString lastName)
{
    _firstName = firstName;
    _lastName = lastName;
}

void Customer::setPhoneNumber(QString &phoneNumber)
{
    _phoneNumber = phoneNumber;
}

void Customer::setEmail(QString &email)
{
    _email = email;
}

void Customer::addReservation(quint32 resID)
{
    _reservations.append(resID);
    _resCount++;
}
