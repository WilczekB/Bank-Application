
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "transaction.h"
#include "calculator.h"
#include <string>
#include <random>
#include <QMessageBox>
#include <QString>
#include <vector>

class Client;

class BankAccount
{
protected:
    //Pole przechowujące numer konta użytkownika
    std::string account_number_;
    //Pole przechowujące saldo konta użytkownika
    double balance_;
    //Pole przechowujące wartość boolean czy konto jest aktywne
    bool isActive_;
    //Wektor wskaźników do obiektów klasy Transaction, który przechowuje transakcje związane z tym kontem
    std::vector<Transaction*> transactions;
    //Pole przechowujące typ konta
    std::string type_;
    //Pole przechowujące indentyfikator właściciela konta
    std::string ownerID;
    //Wskaźnik na obiekt Calculator, który służy do obliczania rat, bądź odsetki
    Calculator* calculator_;
    //Wskaźnik na obiekt Client, który reprezentuje właściciela konta
    Client* owner;
public:
    //Konstruktor
    //@param account_number przechowuje numer konta
    //@param balance przechowuje saldo konta
    //@param isActive przechowuje informacje czy konto jest aktywne
    //@param ownerPesel przechowuje pesel właściciela konta
    //@param type przechowuje informacje o typie konta
    BankAccount(std::string account_number, double balance, bool isActive, std::string ownerPesel, std::string type);
    //Wirtualny destruktor
    virtual ~BankAccount();
    //Funkcja ustawiająca pole isActive_
    //@param isActive
    void setIsActive(bool isAcitve);
    //Funkcja ustawiająca pole balance_
    //@param balance
    void setBalance(double balance);
    //Funkcja ustawiająca pole calculator_
    //@param calculator
    void setCalculator(Calculator* calculator);
    //Funkcja ustawiająca pole account_number_
    void setAccountNumber();
    //Funkcja zwracająca pole account_number_
    std::string getAccountNumber() const;
    //Funkcja zwracająca pole isActive_
    bool getIsActive() const;
    //Funkcja zwracająca pole balance_
    double getBalance() const;
    //Funkcja zwracająca pole transactions
    std::vector<Transaction*> getTransactions() const;
    //Funkcja zwracająca pole owner
    Client* getOwner() const;
    //Funkcja zwracająca id wszystkich transakcji na koncie
    std::vector<int> getTransactionsId() const;
    //Funkcja zwracająca pole ownerID
    std::string getOwnerID() const;
    //Funkcja zwracająca pole calculator_
    Calculator* getCalculator() const;
    //Funkcja wyświetlająca wszystkie transakcje na koncie
    QString showTransactions() const;
    //Wirtualna funkcja przypisująca transakcję do konta
    //@param transaction wskaźnik na obiekt Transaction
    virtual void addTransaction(Transaction* transaction);
    //Czysto wirtualna funkcja wypłacająca środki z konta
    virtual bool withdraw(double amount) = 0;
    //Czysto wirtualna funkcja zwracająca typ konta
    virtual std::string getType() const = 0;
    //Czysto wirtualna funkcja ustawiająca typ konta
    virtual void setType() = 0;
    //Czysto wirtualna funkcja wpłacająca środki na konto
    virtual void deposit(double amount) = 0;
};

#endif // BANKACCOUNT_H
