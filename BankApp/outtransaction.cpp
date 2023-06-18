
#include "outtransaction.h"
#include "bankaccount.h"

/*
 * Konstruktor
 */
OutTransaction::OutTransaction(double amount, const std::string& reciver, const std::string& title, BankAccount* senderAccountNumber)
    : Transaction(amount, reciver, senderAccountNumber->getAccountNumber(), title), senderAccount(senderAccountNumber)
{
    manager = new ClientManager();
    Client *owner = manager->findClient(senderAccount->getOwnerID());
    sender_ = owner->getFullname();
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekt typu BankAccount
 */
OutTransaction::~OutTransaction()
{
    delete senderAccount;
}

/*
 * Funkcja zwracająca informację, że transakcja jest typu wychodzącego
 */
std::string OutTransaction::getType() const
{
    return "OUT";
}

/*
 * Funkcja zwracająca informacje o transkacji
 */
std::string OutTransaction::getInfo() const
{
    return  std::to_string(id) + '\t' + getType() + '\t' + Transaction::getInfo() + '\t' + reciver_;
}
