#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QtGlobal>
#include <QDateTime>
#include "qdatetimespan.h"
#include "view.h"
#include "model.h"

#include <QDebug>


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    
signals:
    
public slots:
    void refreshItemViewData();
    void refreshCustomerViewData();
    void refreshReservationViewData();
    void refreshBookResViewItemList();

    void bookReservation(QStringList textParameters, QList<quint32> numericParameters,
                         QDateTime startTime, QDateTime endTime);

private:
    View * v;
    Model * m;
    
};

#endif // CONTROLLER_H
