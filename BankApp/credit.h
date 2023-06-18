
#ifndef CREDIT_H
#define CREDIT_H

#include "bankaccount.h"
#include <string>
#include <QDate>


class Client;

class Credit : public BankAccount
{
private:
    //Pole przechowujące datę startu kredytu
    QDate start_date_;
    //Pole przechowujące okres finansowania
    int financial_period_;
    //Pola przechowujące wartość inwestycji, oprocentowanie i prowizję
    double investment_value_, percentage_, comission_;
public:
    //Konstruktor
    //@param account_number przechowuje numer konta kredytowego
    //@param balance przechowuje stan salda konta
    //@param start_date przechowuje początkową datę kredytu
    //@param financial_period przechowuje okres finansowania kredytu
    //@param investment_value przechowuje wartość inwestycji
    //@param percentage przechowuje wartość oprocentowania kredytu
    //@param commision przechowuje wartość prowizji kredytu
    //@param ownerPesel przechowuje numer pesel kredytobiorcy
    Credit(std::string account_number, double balance, QDate start_date, int financial_period, double investment_value,
           double percentage, double commision, std::string ownerPesel);
    //Destruktor
    ~Credit();
    //Funkcja ustawiająca wartość pola start_date_
    //@param start_date przechowuje datę startu kredytu
    void setStartDate(QDate start_date);
    //Funkcja ustawiająca wartość pola financial_period_
    //@param financial_period przechowuje okres inwestycji
    void setFinancialPeriod(int financial_period);
    //Funkcja ustawiająca wartość pola investment_value_
    //@param investment_value przechowuje wartość inwestycji
    void setInvestmentValue(double investment_value);
    //Funkcja ustawiająca wartość pola percentage_
    //@param percentage przechowuje oprocentowanie kredytu
    void setPercentage(double percentage);
    //Funkcja ustawiająca wartość pola commision_
    //@param commision przechowuje prowizje kredytu
    void setCommision(double commision);
    //Funkcja zwracająca wartość pola start_date_
    QDate getStartDate() const;
    //Funkcja zwracająca wartość pola financial_period_
    int getFinancialPeriod() const;
    //Funkcja zwracająca wartość pola investment_value_
    double getInvestmentValue() const;
    //Funkcja zwracająca wartość pola commision_
    double getCommision() const;
    //Funkcja zwracająca wartość pola percentage_
    double getPercentage() const;
    //Funkcja wypłacająca środki z konta
    //@param amount ilość środków do wypłaty
    bool withdraw(double amount);
    //Funkcja zwracająca typ konta
    std::string getType() const;
    //Funkcja ustawiająca typ konta
    void setType();
    //Funkcja wpłacająca środki na konto
    //@param amount ilość środków do wpłaty
    void deposit(double amount);
    //Funkcja tworząca harmonogram spłaty kredytu
    void calculateCredit();

};

#endif // CREDIT_H
