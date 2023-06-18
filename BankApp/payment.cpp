
#include "payment.h"

Payment::Payment(QDate date, double capital, double installment, double interest)
{
    this->date = date;
    this->capital = capital;
    this->installment = installment;
    this->date = date;
}

double Payment::getCapital() const
{
    return capital;
}

QDate Payment::getDate() const
{
    return date;
}

double Payment::getInstallment() const
{
    return installment;
}

double Payment::getInterest() const
{
    return interest;
}
