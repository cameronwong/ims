#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QMap>
#include <QtGlobal>
#include <QString>
#include "qmoney.h"
#include "qdatetimespan.h"
#include "customer.h"
#include "item.h"
#include "reservation.h"

#include <QDebug>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
    quint32 addReservation(quint32 &itemID, QDateTimeSpan &timePeriod, QMoney &price, quint8 &paymentMethod,
                        quint8 &location, quint16 &employeeID, quint32 customerID = 0);
    quint32 addCustomer(QString &firstName, QString &lastName, QString &phoneNumber, QString &email);
    void setRelations(quint32 resID, quint32 cusID, quint32 itemID);

    const QMap<quint32, Item> getItemData() const;
    const QMap<quint32, Customer> getCustomerData() const;
    const QMap<quint32, Reservation> getReservationData() const;

    // debug
    void test();

signals:
    void reservationModelChanged();
    void customerModelChanged();
    void itemModelChanged();
    
public slots:

private:
    QMap<quint32, Customer> customerMap;
    QMap<quint32, Item> itemMap;
    QMap<quint32, Reservation> resMap;
    
};

#endif // MODEL_H
