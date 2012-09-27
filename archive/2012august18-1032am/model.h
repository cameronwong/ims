#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QMap>
#include "customer.h"
#include "item.h"
#include "reservation.h"

#include <QDebug>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);

    QMap<quint32, Item> getItemData();

    // debug
    void test();

signals:
    
public slots:

private:
    QMap<quint32, Customer> customerMap;
    QMap<quint32, Item> itemMap;
    QMap<quint32, Reservation> resMap;
    
};

#endif // MODEL_H
