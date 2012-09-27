#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QtGlobal>
#include <QList>

#include <QDebug>

class Customer
{
public:
    Customer();
    Customer(QString &firstName, QString lastName = "", QString phoneNumber = "", QString email = "");

    // CONST MEMBER FUNCTIONS
    quint32 getID() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getName() const;
    QString getPhoneNumber() const;
    QString getEmail() const;
    quint16 getResCount() const;
    QList<quint32> getPastReservations() const;

    // MUTATORS
    void setName(QString firstName, QString lastName = "");
    void setPhoneNumber(QString &phoneNumber);
    void setEmail(QString &email);

private:
    quint32 _myID;
    QString _firstName;
    QString _lastName;
    QString _phoneNumber;
    QString _email;
    quint16 _resCount;
    QList<quint32> _pastReservations;

    static quint32 _currID;
};

#endif // CUSTOMER_H
