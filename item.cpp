#include "item.h"
quint32 Item::_currID = 0;

Item::Item()
{
    _myID = _currID++;
    _itemName = QString("");
    _dateAdded = QDateTime::currentDateTime();
    _bookings = QList<quint32>();

}

Item::Item(QString itemName)
{
    _myID = _currID++;
    _itemName = itemName;
    _dateAdded = QDateTime::currentDateTime();
    _bookings = QList<quint32>();

}

quint32 Item::getID() const
{
    return _myID;
}

QString Item::getName() const
{
    return _itemName;
}

QDateTime Item::getDateAdded() const
{
    return _dateAdded;
}

QList<quint32> Item::getBookings() const
{
    return _bookings;
}

void Item::changeName(QString newName)
{
    _itemName = newName;
}

void Item::addBooking(quint32 refID)
{
    if(!_bookings.contains(refID))
        _bookings.append(refID);
}
