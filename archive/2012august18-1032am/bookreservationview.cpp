#include "bookreservationview.h"

BookReservationView::BookReservationView(QWidget *parent) :
    QWidget(parent)
{
    // ORGANIZATIONAL
    overallLayout = new QVBoxLayout(this);
    bookResLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();
    reservationBox = new QGroupBox(tr("Reservation"), this);
    customerBox = new QGroupBox(tr("Customer"), this);
    paymentBox = new QGroupBox(tr("Payment"), this);
    reservationFormLayout = new QFormLayout(reservationBox);
    customerFormLayout = new QFormLayout(customerBox);
    paymentFormLayout = new QFormLayout(paymentBox);

    // OVERALL LAYOUT
    overallLayout->addLayout(bookResLayout);
    overallLayout->addLayout(buttonLayout);

    // BOOK RESERVATION ROW
    bookResLayout->addStretch();
    bookResLayout->addWidget(reservationBox);
    bookResLayout->addWidget(customerBox);
    bookResLayout->addWidget(paymentBox);

    // RESERVATION FORM
    itemEdit = new QComboBox(this);
    itemIdEdit = new QLineEdit(this);
    startTimeEdit = new QDateTimeEdit(this);
    endTimeEdit = new QDateTimeEdit(this);
    locationEdit = new QComboBox(this);

    reservationFormLayout->addRow(tr("Item"), itemEdit);
    reservationFormLayout->addRow(tr("Item ID"), itemIdEdit);
    reservationFormLayout->addRow(tr("Start Time"), startTimeEdit);
    reservationFormLayout->addRow(tr("End Time"), endTimeEdit);
    reservationFormLayout->addRow(tr("Location"), locationEdit);

    // CUSTOMER FORM
    firstNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);

    customerFormLayout->addRow(tr("First Name"), firstNameEdit);
    customerFormLayout->addRow(tr("Last Name"), lastNameEdit);
    customerFormLayout->addRow(tr("Email"), emailEdit);
    customerFormLayout->addRow(tr("Phone #"), phoneEdit);

    // PAYMENT FORM
    costEdit = new QDoubleSpinBox(this);
    paymentMethodEdit = new QComboBox(this);
    empIdEdit = new QLineEdit(this);

    paymentFormLayout->addRow(tr("Cost"), costEdit);
    paymentFormLayout->addRow(tr("Payment Method"), paymentMethodEdit);
    paymentFormLayout->addRow(tr("Employee ID"), empIdEdit);

    // BUTTONS
    reserveButton = new QPushButton(tr("Reserve"), this);
    cancelButton = new QPushButton(tr("Cancel"), this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(reserveButton);

    // connections
    connect(reserveButton, SIGNAL(clicked()), this, SIGNAL(dialogEnded()));
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(dialogEnded()));


    // LOAD WITH DUMMY DATA
    itemEdit->addItem("Bike 1");
    itemEdit->addItem("Bike 2");
    itemEdit->addItem("Bike 3");
    itemEdit->addItem("Boat 1");
    itemEdit->addItem("Boat 2");
    itemEdit->addItem("Helicopter 1");

    itemIdEdit->setText("0000000121");

    startTimeEdit->setDateTime(QDateTime::currentDateTime());
    endTimeEdit->setDateTime(QDateTime::currentDateTime());

    locationEdit->addItem("Hilo");
    locationEdit->addItem("Lihue");
    locationEdit->addItem("Honolulu");

    firstNameEdit->setText("Russell");
    lastNameEdit->setText("Wong");
    emailEdit->setText("rmwong@hawaii.rr.com");
    phoneEdit->setText("(808) 778-3001");

    costEdit->setValue(78.99);

    paymentMethodEdit->addItem("Cash");
    paymentMethodEdit->addItem("Credit Card");
    paymentMethodEdit->addItem("Debit Card");
    paymentMethodEdit->addItem("PayPal");

    empIdEdit->setText("000748581");

}

void BookReservationView::setDate(QDate date)
{
    startTimeEdit->setDate(date);
    endTimeEdit->setDate(date.addDays(1));
}

void BookReservationView::setItem(int itemID)
{
    itemEdit->setCurrentIndex(itemID);
}
void BookReservationView::loadItemList(QStringList &itemNames)
{
    itemEdit->clear();
    for(qint8 i=0; i<itemNames.size(); i++)
        itemEdit->addItem(itemNames.at(i));
}

void BookReservationView::makeReservation()
{

}
