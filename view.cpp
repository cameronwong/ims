#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    // create
    stackedWidget = new QStackedWidget(this);
    centralWidget = new QWidget(this);

    customerView = new CustomerView(this);
    reservationView = new ReservationView(this);
    itemView = new ItemView(this);
    bookResView = new BookReservationView(this);
    itemAvailView = new ItemAvailabilityView();

    viewLayout = new QVBoxLayout(centralWidget);
    viewFooter = new QLabel(tr("UI Prototype<br>Cameron Wong<br>Summer 2012"));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    // layout
    setCentralWidget(centralWidget);
    layout()->setContentsMargins(0,0,0,0);
    setFixedWidth(width());

    stackedWidget->setFrameStyle(QFrame::NoFrame);
    stackedWidget->addWidget(itemView);
    stackedWidget->addWidget(reservationView);
    stackedWidget->addWidget(customerView);

    viewLayout->setContentsMargins(0,0,0,10);
    viewLayout->addWidget(stackedWidget);
    viewLayout->addWidget(viewFooter);
    viewLayout->addWidget(bookResView);

    // initialize
    setWindowTitle("Inventory Management System");
    setWindowIcon(QIcon(":/icons/vintage-car-icon.png"));
    viewFooter->setAlignment(Qt::AlignCenter);
    stackedWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

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

void View::showBookReservationView()
{
    storedSize = size(); // save window size for restoration after we finish with reserve dialog

    bookResView->setDate(QDate::currentDate());
    itemAvailView->hide();
    viewFooter->hide();
    stackedWidget->setProperty("enabled", false);
    newToolBar->setProperty("enabled", false);
    bookResView->show();
}

void View::bookReservationDialogEnded()
{
    bookResView->hide();
    viewFooter->show();
    resize(storedSize);
    stackedWidget->setProperty("enabled", true);
    newToolBar->setProperty("enabled", true);
}

void View::clearDatabaseDialog()
{
    int r = QMessageBox::warning(this, tr("Inventory Management System"),
                                 tr("Are you sure you want to clear the database?\n"
                                    "This action cannot be undone!"),
                                 QMessageBox::Yes | QMessageBox::Cancel);
    if(r == QMessageBox::Yes)
        emit clearDatabase();
}

void View::showResView()
{
    stackedWidget->setCurrentWidget(reservationView);
}

void View::showItemView()
{
    stackedWidget->setCurrentWidget(itemView);
}

void View::showCustomerView()
{
    stackedWidget->setCurrentWidget(customerView);
}

void View::showAbout()
{
    QMessageBox::about(this, tr("About Inventory Management System"),
                       tr("<h2>Inventory Management System 0.2 (alpha)</h2>"
                          "<p>Copyright &copy; 2012 Reolyze Software Inc."
                          "<p>Inventory Management System is a streamlined application "
                          "for tracking and maintaining a business inventory of any "
                          "size.  IMS can be integrated with a sales system front-end "
                          "for automatic real-time updates and reports on product "
                          "status, sales efficiency, and customer behavior."));
}

void View::createActions()
{
    viewActionGroup = new QActionGroup(this);

    itemViewAction = new QAction(tr("&Inventory View"), this);
    itemViewAction->setActionGroup(viewActionGroup);
    itemViewAction->setIcon(QIcon(":/icons/car-icon-pink.png"));
    itemViewAction->setShortcut(tr("Ctrl+1"));
    itemViewAction->setStatusTip(tr("View current inventory and availability information"));
    connect(itemViewAction, SIGNAL(triggered()), this, SLOT(showItemView()));

    resViewAction = new QAction(tr("&Reservation View"), this);
    resViewAction->setActionGroup(viewActionGroup);
    resViewAction->setIcon(QIcon(":/icons/res-icon.png"));
    resViewAction->setShortcut(tr("Ctrl+2"));
    resViewAction->setStatusTip(tr("View pending and past reservations"));
    connect(resViewAction, SIGNAL(triggered()), this, SLOT(showResView()));

    cusViewAction = new QAction(tr("&Customer View"), this);
    cusViewAction->setActionGroup(viewActionGroup);
    cusViewAction->setIcon(QIcon(":/icons/customer-icon-2.png"));
    cusViewAction->setShortcut(tr("Ctrl+3"));
    cusViewAction->setStatusTip(tr("View list of customers in the database"));
    connect(cusViewAction, SIGNAL(triggered()), this, SLOT(showCustomerView()));

    bookResAction = new QAction(tr("Add &Reservation"), this);
    bookResAction->setIcon(QIcon(":/icons/book-res-icon.png"));
    bookResAction->setShortcut(tr("Ctrl+R"));
    bookResAction->setStatusTip(tr("Add a new reservation to the database"));
    connect(bookResAction, SIGNAL(triggered()), this, SLOT(showBookReservationView()));

    itemViewAction->setCheckable(true);
    itemViewAction->setChecked(true);
    resViewAction->setCheckable(true);
    cusViewAction->setCheckable(true);

    connectAction = new QAction(tr("&Connect..."), this);
    connectAction->setStatusTip(tr("Connect to a different inventory database"));

    clearAction = new QAction(tr("C&lear Database"), this);
    clearAction->setStatusTip(tr("Purge this database of data"));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clearDatabaseDialog()));

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setStatusTip(tr("Exit the application"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    addItemAction = new QAction(tr("Add &Inventory"), this);
    addItemAction->setShortcut(tr("Ctrl+I"));
    addItemAction->setStatusTip(tr("Add a new item to the inventory database"));

    addCustomerAction = new QAction(tr("Add &Customer"), this);
    addCustomerAction->setShortcut(tr("Ctrl+P"));
    addCustomerAction->setStatusTip(tr("Add a customer's contact information to the database"));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Information about &copy; Inventory Management System"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

}

void View::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(connectAction);
    fileMenu->addAction(clearAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(itemViewAction);
    viewMenu->addAction(resViewAction);
    viewMenu->addAction(cusViewAction);

    addMenu = menuBar()->addMenu(tr("&Add"));
    addMenu->addAction(addItemAction);
    addMenu->addAction(bookResAction);
    addMenu->addAction(addCustomerAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);

}

void View::createToolBars()
{
    viewToolBar = addToolBar(tr("&View"));
    viewToolBar->setIconSize(QSize(40,40));

    viewToolBar->addAction(itemViewAction);
    viewToolBar->addAction(resViewAction);
    viewToolBar->addAction(cusViewAction);

    newToolBar = addToolBar(tr("&New"));
    newToolBar->setIconSize(QSize(40,40));
    newToolBar->addAction(bookResAction);
}

void View::createStatusBar()
{

}
