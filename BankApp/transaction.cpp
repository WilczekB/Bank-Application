
#include "transaction.h"

//Inicjalizacja statycznej zmiennej
int Transaction::idCounter = 0;

/*
 * Konstruktor
 */
Transaction::Transaction(double amount, const std::string& reciver, const std::string& senderAccountNumber,
                         const std::string& title) : id(++idCounter), amount_(amount),reciver_(reciver),  sender_acc_number_(senderAccountNumber),
    title_(title)
{

}

/*
 * Destruktor
 */
Transaction::~Transaction()
{

}

/*
 * Funkcja zwracająca id transakcji
 */
int Transaction::getId() const
{
    return id;
}

/*
 * Funkcja zwracająca wielkość kwoty transakcji
 */
double Transaction::getAmount() const
{
    return amount_;
}

/*
 * Funkcja zwracająca odbiorcę transakcji
 */
const std::string& Transaction::getReciver() const
{
    return reciver_;
}

/*
 * Funkcja zwracająca nadawcę transakcji
 */
const std::string& Transaction::getSender() const
{
    return sender_;
}

/*
 * Funkcja zwracająca numer konta nadawcy transakcji
 */
const std::string& Transaction::getSenderAccNumber() const
{
    return sender_acc_number_;
}

/*
 * Funkcja zwracająca tytuł transakcji
 */
const std::string& Transaction::getTitle() const
{
    return title_;
}

/*
 * Funkcja zwracająca informacje na temat transakcji
 */
std::string Transaction::getInfo() const
{
    return std::to_string(amount_) + '\t' + title_;
}
