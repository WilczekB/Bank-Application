#include "bankaccount.h"
#include "credit.h"
#include "client.h"

/*
 * Konstruktor
 */
Credit::Credit(std::string account_number, double balance, QDate start_date, int financial_period, double investment_value, double percentage, double commision, std::string ownerPesel)
    : BankAccount(account_number, balance, true, ownerPesel, "Kredyt"), start_date_(start_date), financial_period_(financial_period),
    investment_value_(investment_value), percentage_(percentage), comission_(commision)
{

}

/*
 * Destruktor
 */
Credit::~Credit()
{

}

/*
 * Funkcja ustawiająca datę rozpoczęcia kredytu
 */
void Credit::setStartDate(QDate start_date)
{
    start_date_ = start_date;
}

/*
 * Funkcja ustawiająca okres finansowania kredytu
 */
void Credit::setFinancialPeriod(int financial_period)
{
    financial_period_ = financial_period;
}

/*
 * Funkcja ustawiająca wartość kredytu
 */
void Credit::setInvestmentValue(double investment_value)
{
    investment_value_ = investment_value;
}

/*
 * Funkcja ustawiająca oprocentowanie kredytu
 */
void Credit::setPercentage(double percentage)
{
    percentage_ = percentage;
}

/*
 * Funkcja ustawiająca prowizję kredytu
 */
void Credit::setCommision(double commision)
{
    comission_ = commision;
}

/*
 * Funkcja zwracająca datę rozpoczęcia kredytu
 */
QDate Credit::getStartDate() const
{
    return start_date_;
}

/*
 * Funkcja zwracająca okres finansowania kredytu
 */
int Credit::getFinancialPeriod() const
{
    return financial_period_;
}

/*
 * Funkcja zwracająca wartość kredytu
 */
double Credit::getInvestmentValue() const
{
    return investment_value_;
}

/*
 * Funkcja zwracająca oprocentowanie kredytu
 */
double Credit::getPercentage() const
{
    return percentage_;
}

/*
 * Funkcja zwracająca prowizję kredytu
 */
double Credit::getCommision() const
{
    return comission_;
}

/*
 * Funkcja umożliwiająca wypłacenie środków z konta
 */
bool Credit::withdraw(double amount)
{
    //Warunek sprawdzający, czy żądana kwota nie jest większa od salda konta
    if(amount <= balance_){

        //W przypadku, gdy kwota jest mniejsza odejmujemy ją od salda
        balance_ -= amount;

        //Zwrócenie wartości true w ramach potwierdzenia wypłaty
        return true;
    }

    //Zwrócenie wartości false w przypadku braku wypłacenia środków z konta
    return false;
}

/*
 * Funkcja zwracająca typ konta
 */
std::string Credit::getType() const
{
    std::string type = "Kredyt";
    return type;
}

void Credit::setType()
{
    type_ = "Kredyt";
}

void Credit::deposit(double amount)
{
    //Dodanie żądanej kwoty do salda konta
    balance_ += amount;
}

void Credit::calculateCredit()
{
    calculator_->calculate();
}
