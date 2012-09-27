#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QCalendarWidget>
#include <QHeaderView>
#include <QMap>
#include "item.h"
#include "bookreservationview.h"

#include <QDebug>

class ItemView : public QWidget
{
    Q_OBJECT
public:
    explicit ItemView(QWidget *parent = 0);
    void initializeData();

    // FROM CONTROLLER
    void loadData(QMap<quint32, Item> data);

signals:
    // TO CONTROLLER
    void refreshData();

    // TO VIEW
    void itemAvailRequested(QString itemName, int id);

public slots:
    void itemSelected(int row);
    void launchBookReservation(QDate date);

protected:
    QSize sizeHint() const;

private:
    QTableWidgetItem * newEntry(QString text);
    QVBoxLayout *itemViewLayout;

    QTableWidget *itemTable;
};

#endif // ITEMVIEW_H
