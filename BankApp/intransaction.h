
#ifndef IN_TRANSACTION_H
#define IN_TRANSACTION_H

#include "transaction.h"
/*
#include "bankaccount.h"
#include "client.h"
*/
class InTransaction : public Transaction {
public:
    //Konstruktor
    //@param amount przechowuje wartość kwoty transakcji
    //@param sender przechowuje imie i nazwisko wysyłającego transakcję
    //@param senderAccountNumber przechowuje numer konta wysyłającego transakcję
    //@param title przechowuje tytuł transakcji
    InTransaction(double amount, const std::string& sender, const std::string& senderAccountNumber, const std::string& title);
    //Funkcja zwracająca typ transakcji
    std::string getType() const override;
    //Funkcja zwracająca informacje o transakcji
    std::string getInfo() const override;
};

#endif // IN_TRANSACTION_H

