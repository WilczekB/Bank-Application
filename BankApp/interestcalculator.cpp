
#include "interestcalculator.h"
#include "savingsaccount.h"

/*
 * Konstruktor
 */
InterestCalculator::InterestCalculator(SavingsAccount* savingAccount) : account(savingAccount)
{

}

/*
 * Destruktor
 */
InterestCalculator::~InterestCalculator()
{
    //Zwolnienie pamięci zajmowanej przez obiekt SavingsAccount
    delete account;
}

/*
 * Funkcja wyliczająca odsetki dla konta oszczędnościowego
 */
void InterestCalculator::calculate()
{
    //Pobranie oprocentowania i salda konta
    double interest_rate = account->getInterestRate();
    double balance = account->getBalance();

    //Obliczenie odsetek
    double interest = balance * interest_rate;

    //Dokonanie wpłaty odsetek na konto
    account->deposit(interest);
}

