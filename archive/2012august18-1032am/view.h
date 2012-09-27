#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QCursor>
#include <QSize>
#include <QPoint>

#include "customerview.h"
#include "reservationview.h"
#include "itemview.h"
#include "bookreservationview.h"
#include "itemavailabilityview.h"

#include <QDebug>

class View : public QWidget
{
    Q_OBJECT
    
public:
    View(QWidget *parent = 0);
    ~View();
    CustomerView * getCustomerView();
    ReservationView * getReservationView();
    ItemView * getItemView();
    BookReservationView * getBookReservationView();
    ItemAvailabilityView * getItemAvailabilityView();

public slots:
    void showItemAvail(QString title, int itemID);
    void showBookReservationView(QDate date);
    void bookReservationDialogEnded();

private:
    QVBoxLayout *viewLayout;

    QTabWidget *tabView;
    QLabel *viewHeader;
    QLabel *viewFooter;

    CustomerView *customerView;
    ReservationView *reservationView;
    ItemView *itemView;
    BookReservationView *bookResView;
    ItemAvailabilityView *itemAvailView;

    QSize storedsize;


};

#endif // VIEW_H
