
#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "bankaccount.h"
#include "client.h"

class BankAccount;
class Client;

class SavingsAccount : public BankAccount
{
private:
    //Pole przechowujące wartość odsetek
    double interest_rate;
    //Pole przechowujące limit wypłat bez opłaty
    int withdrawal_limit;
    //Statyczne pole przechowujące ilość zrealizowanych transakcji
    static int withdrawal_counter;
public:
    //Konstruktor
    //@param account_number przechowuje numer konta oszczędnościowego
    //@param balance przechowuje wartość salda konta
    //@param interest_rate_ przechowuje wartość odsetek
    //@param withdrawal_limit_ przechowuje wartość limitu transakcji
    //@param ownerPesel przechowuje numer pesel właściciela konta
    SavingsAccount(std::string account_number, double balance, double interest_rate_, int withdrawal_limit_, std::string ownerPesel);
    //Destruktor
    ~SavingsAccount();
    //Funkcja ustawiająca wartość pola withdrawal_limit
    //@param withdrawal_limit_ przechowuje wartość limitu transakcji
    void setWithdrawalLimit(int withdrawal_limit);
    //Funkcja ustawiająca wartość pola interest_rate
    //@param interest_rate_ przechowuje wartość odsetek
    void setInterestRate(double interest_rate);
    //Funkcja zwracająca wartość pola interest_rate
    double getInterestRate() const;
    //Funkcja zwracająca wartość pola withdrawal_limit
    int getWithdrawalLimit() const;
    //Funkcja realizująca wpłacanie środków na konto
    //@param amount przechowuje kwotę do wpłaty
    void deposit(double amount);
    //Funkcja realizująca wypłacanie środków z konta
    //@param amount przechowuje kwotę do wypłaty
    bool withdraw(double amount);
    //Funkcja zwracająca typ konta
    std::string getType() const;
    //Funkcja ustawiająca typ konta
    void setType();
};

#endif // SAVINGSACCOUNT_H
