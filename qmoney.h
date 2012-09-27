#ifndef QMONEY_H
#define QMONEY_H

#include <QtGlobal>
#include <QString>

class QMoney
{
public:
    QMoney();
    QMoney(const QMoney &toCopy);
    QMoney(quint32 dollars, quint8 cents);

    QMoney & operator=(const QMoney &rhs);
    QMoney & operator+=(const QMoney &rhs);
    QMoney & operator-=(const QMoney &rhs);
    QMoney & operator*=(quint32 coeff);
    const QMoney operator*(quint32 coeff);
    const QMoney operator+(const QMoney &other) const;
    const QMoney operator-(const QMoney &other) const;

    bool operator==(const QMoney &other) const;
    bool operator!=(const QMoney &other) const;
    bool operator>=(const QMoney &other) const;
    bool operator>(const QMoney &other) const;
    bool operator<=(const QMoney &other) const;
    bool operator<(const QMoney &other) const;

    quint8 getCents() const;
    quint32 getDollars() const;
    QString toString() const;

private:
    quint8 _cents;
    quint32 _dollars;
};


#endif // QMONEY_H
