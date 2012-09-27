#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    // create
    stackedWidget = new QStackedWidget(this);

    customerView = new CustomerView(this);
    reservationView = new ReservationView(this);
    itemView = new ItemView(this);
    bookResView = new BookReservationView(this);
    itemAvailView = new ItemAvailabilityView();

    viewLayout = new QVBoxLayout(this);
    viewFooter = new QLabel(tr("UI Prototype<br>Cameron Wong<br>Summer 2012"));

    // layout
    stackedWidget->addTab(itemView, tr("Inventory"));
    tabView->addTab(reservationView, tr("Reservations"));
    tabView->addTab(customerView, tr("Customers"));

    viewLayout->addWidget(tabView);
    viewLayout->addWidget(viewFooter);
    viewLayout->addWidget(bookResView);

    // initialize
    setWindowTitle("ReoIMS");
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
    storedSize = size(); // save window size for restoration after we finish with reserve dialog

    bookResView->setDate(date);
    itemAvailView->hide();
    viewFooter->hide();
    stackedWidget->setProperty("enabled", false);
    bookResView->show();
}

void View::bookReservationDialogEnded()
{
    bookResView->hide();
    viewFooter->show();
    resize(storedSize);
    stackedWidget->setProperty("enabled", true);
}
