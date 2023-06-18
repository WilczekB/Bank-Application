
#include "intransaction.h"

/*
 * Konstruktor
 */
InTransaction::InTransaction(double amount, const std::string& sender, const std::string& senderAccountNumber, const std::string& title)
    : Transaction(amount, "", senderAccountNumber, title)
{
    sender_ = sender;
}

/*
 * Funkcja zwracająca informację, że transakcja jest typu przychodzącego
 */
std::string InTransaction::getType() const
{
    return "IN";
}

/*
 * Funkcja zwracająca informacje o transkacji
 */
std::string InTransaction::getInfo() const
{
    return std::to_string(id) + '\t' + getType() + ' ' + Transaction::getInfo() + '\t' + sender_ + '\t' + sender_acc_number_;
}
