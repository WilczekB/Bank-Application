
#ifndef INTERESTCALCULATOR_H
#define INTERESTCALCULATOR_H

#include "savingsaccount.h"
#include "calculator.h"

class SavingsAccount;

class InterestCalculator : public Calculator
{
private:
    //Wskaźnik na obiekt klasy SavingsAccount
    SavingsAccount* account;
public:
    //Konstruktor
    //@param savingAccount wskaźnik na obiekt klasy SavingsAccount
    InterestCalculator(SavingsAccount* savingAccount);
    //Destruktor
    ~InterestCalculator();
    //Funkcja wyliczająca odsetki
    void calculate() override;
};

#endif // INTERESTCALCULATOR_H
