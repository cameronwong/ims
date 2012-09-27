#ifndef RESERVATIONVIEW_H
#define RESERVATIONVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QHash>
#include "reservation.h"

class ReservationView : public QWidget
{
    Q_OBJECT
public:
    explicit ReservationView(QWidget *parent = 0);
    void initializeData();

    // FROM CONTROLLER
    void loadData(QList<QStringList> data);

signals:
    // TO CONTROLLER
    void refreshData();
    
public slots:

protected:
    QSize sizeHint() const;

private:
    QTableWidgetItem * newEntry(QString text);
    QVBoxLayout *resViewLayout;

    QTableWidget *resTable;
    
};

#endif // RESERVATIONVIEW_H
