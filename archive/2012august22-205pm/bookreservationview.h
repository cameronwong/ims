#ifndef BOOKRESERVATIONVIEW_H
#define BOOKRESERVATIONVIEW_H

#include <QWidget>
#include <QList>
#include <QStringList>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

class BookReservationView : public QWidget
{
    Q_OBJECT
public:
    explicit BookReservationView(QWidget *parent = 0);

    void setDate(QDate date);
    void setItem(int itemID);

    void loadItemList(QStringList itemNames);
    
signals:
    // TO CONTROLLER
    void sendReservation(QStringList textParameters, QList<quint32> numericParameters,
                         QDateTime startTime, QDateTime endTime);
    void refreshItemList();

    // TO VIEW
    void dialogEnded();
    
public slots:
    // PREP WORK, TO CONTROLLER
    void makeReservation();

private:
    // ORGANIZATIONAL
    QVBoxLayout *overallLayout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *bookResLayout;
    QGroupBox *reservationBox;
    QGroupBox *customerBox;
    QGroupBox *paymentBox;
    QFormLayout *reservationFormLayout;
    QFormLayout *customerFormLayout;
    QFormLayout *paymentFormLayout;

    // RESERVATION FORM ELEMENTS
    QComboBox *itemEdit;
    QDateTimeEdit *startTimeEdit;
    QDateTimeEdit *endTimeEdit;
    QComboBox *locationEdit;

    // CUSTOMER FORM ELEMENTS
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *emailEdit;
    QLineEdit *phoneEdit;

    // PAYMENT FORM ELEMENTS
    QDoubleSpinBox *costEdit;
    QComboBox *paymentMethodEdit;
    QLineEdit *empIdEdit;

    // BUTTONS
    QPushButton *reserveButton;
    QPushButton *cancelButton;

};

#endif // BOOKRESERVATIONVIEW_H
