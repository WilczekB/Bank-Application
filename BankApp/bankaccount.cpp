#include "transaction.h"
#include "intransaction.h"
#include "outtransaction.h"
#include "creditcalculator.h"
#include "interestcalculator.h"
#include "calculator.h"
#include "client.h"

/*
 * Konstruktor
 */
BankAccount::BankAccount(std::string account_number, double balance, bool isActive, std::string ownerPesel, std::string type) :
    account_number_(account_number), balance_(balance), isActive_(isActive), ownerID(ownerPesel), type_(type)
{

    //Sprawdzenie typu konta i utworzenie odpowiedniego obiektu kalkulatora
    if(type_  == "Kredyt")
    {
        //Utworzenie nowego obiektu typu CreditCalculator
        calculator_ = new CreditCalculator(dynamic_cast<Credit*>(this));

    }else if(type_ == "Konto"){

        //Utworzenie nowego obiektu typu InterestCalculator
        calculator_ = new InterestCalculator(dynamic_cast<SavingsAccount*>(this));

    }else{
        //Rzucenie wyjątku w przypadku nieznanego typu konta
        throw std::runtime_error("Nieznany typ konta");
    }
}

/*
 * Destruktor
 */
BankAccount::~BankAccount()
{
    //Usuwanie wszystkich transakcji na koncie
    for(Transaction* transaction : transactions)
    {
        delete transaction;
    }

    //Usuwanie obiektu kalkulatora
    delete calculator_;

    //Usuwanie obiektu właściciela
    delete owner;
}

/*
 * Funkcja ustawiająca saldo konta
 */
void BankAccount::setBalance(double balance)
{
    balance_ = balance;
}

/*
 * Funkcja ustawiająca czy konto jest aktywne
 */
void BankAccount::setIsActive(bool isActive)
{
    isActive_ = isActive;
}

/*
 * Funkcja zwracająca czy konto jest aktywne
 */
bool BankAccount::getIsActive() const
{
    return isActive_;
}

/*
 * Funkcja zwracająca saldo konta
 */
double BankAccount::getBalance() const
{
    return balance_;
}

QString BankAccount::showTransactions() const
{
    //Inicjalizacja zmiennej do przechowywania informacji o transakcji
    QString description = "";

    //Pętla for() iterująca po wszystkich transakcjach na koncie
    for(Transaction* transaction : transactions)
    {
        //Sprawdzenie typu transakcji przy użyciu dynamic_cast
        if(dynamic_cast<InTransaction*>(transaction))
        {
            //Jeśli transakcja jest typu InTransaction, przekaż jej informacje do opisu
            description += QString::fromStdString(transaction->getInfo()) + '\n';

        }else if(dynamic_cast<OutTransaction*>(transaction)){
            //Jeśli transakcja jest typu OutTransaction, przekaż jej informacje do opisu
            description += QString::fromStdString(transaction->getInfo()) + '\n';
        }
    }

    //Zwrócenie opisu transakcji
    return description;
}

/*
 * Funkcja dodająca transakcję do vectora transactions
 */
void BankAccount::addTransaction(Transaction *transaction)
{
    transactions.push_back(transaction);
}

/*
 * Funkcja zwracająca numer konta bankowego
 */
std::string BankAccount::getAccountNumber() const
{
    return account_number_;
}

/*
 * Funkcja ustawiająca kalkulator
 */
void BankAccount::setCalculator(Calculator *calculator)
{
    calculator_ = calculator;
}

/*
 * Funkcja zwracająca właściciela konta
 */
Client* BankAccount::getOwner() const
{
    return owner;
}

/*
 * Funkcja zwracająca wszystkie transakcje na koncie
 */
std::vector<Transaction*> BankAccount::getTransactions() const
{
    return transactions;
}

/*
 * Funkcja zwrająca pesel właściciela konta
 */
std::string BankAccount::getOwnerID() const
{
    return ownerID;
}

std::vector<int> BankAccount::getTransactionsId() const
{

    std::vector<int> transactionsID;

    for(const auto& transaction : transactions)
    {
        transactionsID.push_back(transaction->getId());
    }

    return transactionsID;
}

void BankAccount::setAccountNumber()
{
    //Generowanie losowego numeru konta
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,9);
    for(int i=0; i < 26; i++)
    {
        account_number_ += std::to_string(dis(gen));
    }
}

Calculator* BankAccount::getCalculator() const
{
    return calculator_;
}
