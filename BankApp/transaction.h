
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
/*
#include "client.h"
#include "intransaction.h"
#include "outtransaction.h"
*/
class Transaction
{
protected:
    //Pole przechowujące wartość transakcji
    double amount_;
    //Pole przechowujące numer konta nadawcy
    std::string sender_acc_number_;
    //Pole przechowujące numer konta odbiorcy
    std::string reciver_acc_number_;
    //Pole przechowujące tytuł transakcji
    std::string title_;
    //Pole przechowujące imie i nazwisko odbiorcy
    std::string reciver_;
    //Pole przechowujące imie i nazwisko nadawcy
    std::string sender_;
    //Pole przechowujące id transakcji
    int id;
    //Statyczne pole przechowujące ogólną ilość transakcji na koncie
    static int idCounter;

public:
    //Konstruktor
    //@param amount przechowuje kwotę transakcji
    //@param reciver przechowuje imie i nazwisko odbiorcy transakcji
    //@param senderAccountNumber przechowuje numer konta nadawcy transakcji
    //@param title przechowuje tytuł transakcji
    Transaction(double amount, const std::string& reciver, const std::string& senderAccountNumber,
                const std::string& title);
    //Wirtualny destruktor
    virtual ~Transaction();
    //Funkcja zwracająca wartość pola amount_
    double getAmount() const;
    //Funkcja zwracająca wartość sender_
    const std::string& getSender() const;
    //Funkcja zwracająca wartośc pola reciver_
    const std::string& getReciver() const;
    //Funkcja zwracająca wartość pola reciver_acc_number_
    const std::string& getReciverAccNumber() const;
    //Funkcja zwracająca wartość pola sender_acc_number_
    const std::string& getSenderAccNumber() const;
    //Funkcja zwracająca wartość pola title_
    const std::string& getTitle() const;
    //Funkcja zwracająca wartość pola id
    int getId() const;
    //Wirtualna funkcja zwracająca typ transakcji
    virtual std::string getType() const = 0;
    //Wirtualna funkcja zwracająca informacje o transakcji
    virtual std::string getInfo() const;
};

#endif // TRANSACTION_H
