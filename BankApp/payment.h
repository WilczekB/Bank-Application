
#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDate>


class Payment
{
private:
    QDate date;
    double capital, installment, interest;
public:
    Payment(QDate date, double capital, double installment, double interest);
    double getCapital() const;
    double getInstallment() const;
    double getInterest() const;
    QDate getDate() const;
};

#endif // PAYMENT_H
