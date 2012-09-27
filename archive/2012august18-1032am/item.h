#ifndef ITEM_H
#define ITEM_H

#include <QtGlobal>
#include <QDateTime>
#include <QList>

class Item
{
public:
    Item();
    Item(QString itemName);

    // CONST MEMBER FUNCTIONS
    quint32 getID() const;
    QString getName() const;
    QDateTime getDateAdded() const;
    QList<quint32> getBookings() const;
    bool available() const;
    QString availableText() const;

    // MUTATORS
    void changeName(QString newName);
    void addBooking(quint32 refID);

private:
    quint32 _myID;
    QString _itemName;
    QDateTime _dateAdded;
    QList<quint32> _bookings;
    bool _available;

    static quint32 _currID;
};

#endif // ITEM_H
