
#ifndef OUTTRANSACTION_H
#define OUTTRANSACTION_H

#include "transaction.h"
#include "bankaccount.h"
#include "clientmanager.h"

class BankAccount;

class OutTransaction : public Transaction{
public:
    //Konstruktor
    //@param amount przechowuje kwotę transakcji
    //@param reciver przechowuje imię i nazwisko odbiorcy transakcji
    //@param title przechowuje tytuł transakcji
    //@param senderAccountNumber przechowuje numer konta wysyłającego transakcję
    OutTransaction(double amount, const std::string& reciver, const std::string& title, BankAccount* senderAccountNumber);
    //Destruktor
    ~OutTransaction();
    //Funkcja zwracająca typ transakcji
    std::string getType() const override;
    //Funkcja zwracająca informacje o transakcji
    std::string getInfo() const override;
private:
    //Wskaźnik na obiekt klasy BankAccount
    BankAccount* senderAccount;
    //Wskaźnik na obiekt klasy ClientManager
    ClientManager *manager;
};

#endif // OUTTRANSACTION_H
