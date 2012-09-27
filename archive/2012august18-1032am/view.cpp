#include "view.h"

View::View(QWidget *parent)
    : QWidget(parent)
{
    // create
    tabView = new QTabWidget(this);

    customerView = new CustomerView(this);
    reservationView = new ReservationView(this);
    itemView = new ItemView(this);
    bookResView = new BookReservationView(this);
    itemAvailView = new ItemAvailabilityView();

    viewLayout = new QVBoxLayout(this);
    viewHeader = new QLabel(tr("<b><font size=5>Inventory Management System</font></b>"), this);
    viewFooter = new QLabel(tr("UI Prototype<br>Cameron Wong<br>Summer 2012"));

    // layout
    tabView->addTab(itemView, tr("Inventory"));
    tabView->addTab(reservationView, tr("Reservations"));
    tabView->addTab(customerView, tr("Customers"));

    viewLayout->addWidget(viewHeader);
    viewLayout->addWidget(tabView);
    viewLayout->addWidget(viewFooter);
    viewLayout->addWidget(bookResView);

    // initialize
    setWindowTitle("ReoIMS");
    viewHeader->setAlignment(Qt::AlignCenter);
    viewFooter->setAlignment(Qt::AlignCenter);
    tabView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

    bookResView->setVisible(false);
    itemAvailView->setVisible(false);

    // connections
    connect(itemView, SIGNAL(itemAvailRequested(QString,int)), this, SLOT(showItemAvail(QString,int)));
    connect(itemAvailView->getCalendar(), SIGNAL(activated(QDate)), this, SLOT(showBookReservationView(QDate)));
    connect(bookResView, SIGNAL(dialogEnded()), this, SLOT(bookReservationDialogEnded()));
}

View::~View()
{
    itemAvailView->deleteLater();
}

CustomerView * View::getCustomerView()
{
    return customerView;
}

ReservationView * View::getReservationView()
{
    return reservationView;
}

ItemView * View::getItemView()
{
    return itemView;
}

BookReservationView * View::getBookReservationView()
{
    return bookResView;
}

ItemAvailabilityView * View::getItemAvailabilityView()
{
    return itemAvailView;
}

void View::showItemAvail(QString title, int itemID)
{
    QPoint cursorPos = QCursor::pos();
    cursorPos.rx() -= 40;
    cursorPos.ry() -= 20;
    itemAvailView->move(cursorPos);
    itemAvailView->show();
    itemAvailView->setHeader(title.append(" Availability"));
    bookResView->setItem(itemID);
}

void View::showBookReservationView(QDate date)
{
    storedsize = size(); // save window size for restoration after we finish with reserve dialog

    bookResView->setDate(date);
    itemAvailView->hide();
    viewFooter->hide();
    tabView->setProperty("enabled", false);
    bookResView->show();
}

void View::bookReservationDialogEnded()
{
    bookResView->hide();
    viewFooter->show();
    resize(storedsize);
    tabView->setProperty("enabled", true);
}
