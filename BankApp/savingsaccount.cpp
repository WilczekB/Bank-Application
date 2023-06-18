#include "savingsaccount.h"
#include "bankaccount.h"
#include "client.h"

//Inicjalizacja statycznej zmiennej
int SavingsAccount::withdrawal_counter = 0;

/*
 * Konstruktor
 */
SavingsAccount::SavingsAccount(std::string account_number, double balance, double interest_rate_, int withdrawal_limit_, std::string ownerPesel) : BankAccount(account_number, balance, true, ownerPesel, "Konto"), interest_rate(interest_rate_),
    withdrawal_limit(withdrawal_limit_)
{

}

/*
 * Destruktor
 */
SavingsAccount::~SavingsAccount()
{

}

/*
 * Funkcja ustawiająca odsetki dla konta
 */
void SavingsAccount::setInterestRate(double interest_rate)
{
    this->interest_rate = interest_rate;
}

/*
 * Funkcja ustawiająca limit wypłat dla konta
 */
void SavingsAccount::setWithdrawalLimit(int withdrawal_limit)
{
    this->withdrawal_limit = withdrawal_limit;
}

/*
 * Funkcja zwracająca odsetki dla konta
 */
double SavingsAccount::getInterestRate() const
{
    return interest_rate;
}

/*
 * Funkcja zwracająca limit wypłat dla konta
 */
int SavingsAccount::getWithdrawalLimit() const
{
    return withdrawal_limit;
}

/*
 * Funkcja umożliwiająca wypłacenie środków z konta
 */
bool SavingsAccount::withdraw(double amount)
{
    //Inicjalizacja zmiennej przechowującej wysokość opłaty za wypłatę z konta
    double charge = 2.50;

    //Warunek sprawdzający limit wypłat
    if(withdrawal_counter <= withdrawal_limit)
    {
        //Warunek sprawdzający czy kwota do wypłacenia nie przewyższa salda konta
        if(amount <= balance_){

            //Odjęcie kwoty od salda
            balance_ -= amount;

            //Zwiększenie licznika wypłat
            withdrawal_counter += 1;

            //Zwrócenie wartości true w ramach potwierdzenia wypłaty
            return true;
        }
    }else if(withdrawal_counter >= withdrawal_limit){ //W przypadku przekroczenia limitu wypłat
        //Warunek sprawdzający czy kwota do wypłacenia i opłata nie przewyższa salda konta
        if((amount + charge) <= balance_){

            //Odjęcie kwoty od salda
            balance_ -= amount + charge;

            //Zwiększenie licznika wypłat
            withdrawal_counter += 1;

            //Zwrócenie wartości true w ramach potwierdzenia wypłaty
            return true;
        }
    }

    //Zwrócenie wartości false w przypadku braku wypłacenia środków z konta
    return false;
}

/*
 * Funkcja zwracająca typ konta
 */
std::string SavingsAccount::getType() const
{
    std::string type = "Konto";
    return type;
}

/*
 * Funkcja służąca do wpłacania środków na konto oszczędnościowe
 */
void SavingsAccount::deposit(double amount)
{
    //Dodanie żądanej kwoty do salda konta
    balance_ += amount;
}

void SavingsAccount::setType()
{
    type_ = "Konto";
}
