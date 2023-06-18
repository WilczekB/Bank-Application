
#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "bankaccount.h"
#include "client.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

class BankAccount;
class Client;

class AccountManager
{
private:
    std::vector<BankAccount*> accounts;
    Client* client_;
public:
    //Konstruktor
    //@param Client *client
    AccountManager(Client* client);
    //Destruktor
    ~AccountManager();
    //Funkcja wysyłająca transakcję do drugiego użytkownika
    //@param accountNumber
    //@param reciver
    //@param senderAccNumber
    //@param amount
    //@param title
    bool sendTransaction(const std::string& accountNumber, const std::string& reciver, const std::string& senderAccNumber, double amount, const std::string& title);
    //Funkcja dodająca pieniądze do konta użytkownika
    //@param amount
    //@param account
    void addMoney(double amount, BankAccount* account);
    //Funkcja pobierająca pieniądze z konta użytkownika
    //@param amount
    //@param account
    void takeMoney(double amount, BankAccount* account);
    //Funkcja obliczająca saldo
    double calculateBalance();
    //Funkcja obliczająca zysk
    double calculateProfit();
    //Funkcja obliczająca wydatki
    double calcualteExpanse();
    //Funkcja dodająca konto do systemu
    //@param account
    void addAccount(BankAccount* account);
    //Funkcja usuwająca konto z systemu
    bool removeAccount(BankAccount* account);
    //Funkcja wczytująca konta z pliku tekstowego
    //@param file_name
    void readAccounts(const std::string file_name);
    //Funkcja wczytująca transakcje do pliku tekstowego
    //@param file_name
    //@param account
    void readTransactions(const std::string file_name, BankAccount *account);
    //Funkcja zapisująca konta do plikut tekstowego
    //@param file_name
    void writeAccounts(const std::string file_name);
    //Funkcja zapisująca transakcje do pliku tekstowego
    //@param file_name
    //@param account
    void writeTransactions(const std::string file_name, BankAccount *account);
    //Funkcja znajdująca konto po jego numerze
    //@param accountNumber
    BankAccount* findAccount(const std::string& accountNumber) const;
    //Funkcja znajdująca konto po jego właścicielu
    //@param idOwner
    std::vector<BankAccount*> findByOwner(const std::string& idOwner) const;
    std::string randomizeAmount();
};

#endif // ACCOUNTMANAGER_H
