#include "qmoney.h"

QMoney::QMoney()
{
    _cents = 0;
    _dollars = 0;
}

QMoney::QMoney(const QMoney &toCopy)
{
    _cents = toCopy._cents;
    _dollars = toCopy._dollars;
}

QMoney::QMoney(quint32 dollars, quint8 cents)
{
    _cents = cents;
    _dollars = dollars;
}

QMoney & QMoney::operator=(const QMoney &rhs)
{
    //No need for self-check, everythings on stack.
    _cents = rhs._cents;
    _dollars = rhs._dollars;

    return *this;
}

// FAIL CONDITION: dollars can overflow
QMoney & QMoney::operator+=(const QMoney &rhs)
{
    _cents += rhs._cents;
    _dollars = rhs._dollars + _dollars + (_cents / 100);
    _cents %= 100;

    return *this;
}

QMoney & QMoney::operator -=(const QMoney &rhs)
{
    qint32 tempdollars = (qint32) _dollars;
    qint8 tempcents = (qint8) _cents;

    tempcents -= rhs._cents;
    tempdollars -= rhs._dollars;

    if(tempcents < 0)
    {
        tempdollars--;
        tempcents += 100;   //borrow a dollar for subtraction
    }

    Q_ASSERT(tempdollars > 0);

    _dollars = (quint32) tempdollars;
    _cents = (qint8) tempcents;

    return *this;
}

QMoney & QMoney::operator *=(quint32 coeff)
{
    quint32 tempcents = _cents;
    tempcents *= coeff;

    _dollars *= coeff;
    _dollars += (tempcents / 100);

    tempcents %= 100;
    _cents = (quint8) tempcents;

    return *this;
}

const QMoney QMoney::operator*(quint32 coeff)
{
    return QMoney(*this) *= coeff;
}

const QMoney QMoney::operator+(const QMoney &other) const
{
    return QMoney(*this) += other;
}

const QMoney QMoney::operator-(const QMoney &other) const
{
    return QMoney(*this) -= other;
}

bool QMoney::operator==(const QMoney &other) const
{
    if(_dollars == other._dollars && _cents == other._cents)
        return true;
    else
        return false;
}

bool QMoney::operator!=(const QMoney &other) const
{
    return !(*this == other);
}

bool QMoney::operator>=(const QMoney &other) const
{
    if(_dollars > other._dollars)
        return true;

    else if(_dollars == other._dollars && _cents >= other._cents)
        return true;

    else
        return false;
}

bool QMoney::operator>(const QMoney &other) const
{
    return !(*this <= other);
}


bool QMoney::operator<=(const QMoney &other) const
{
    if(_dollars < other._dollars)
        return true;

    else if(_dollars == other._dollars && _cents <= other._cents)
        return true;

    else
        return false;
}

bool QMoney::operator<(const QMoney &other) const
{
    return !(*this >= other);
}

quint8 QMoney::getCents() const
{
    return _cents;
}

quint32 QMoney::getDollars() const
{
    return _dollars;
}

QString QMoney::toString() const
{
    QString centsString, dollarsString, output;

    centsString.setNum(_cents);
    dollarsString.setNum(_dollars);

    output.prepend("$");
    output.append(dollarsString);
    output.append(".");
    output.append(centsString);

    return output;
}

