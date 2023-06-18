
#ifndef CREDITSCHEDULE_H
#define CREDITSCHEDULE_H

#include "accountmanager.h"
#include "client.h"
#include <fstream>
#include <sstream>
#include <vector>

class CreditSchedule
{
private:
    //Pole przechowujące okres finansowania
    std::string financialPeriod_;
    //Pole przechowującae wartość inwestycji
    std::string investmentValue_;
    //Pole przechowujące datę startu kredytu
    std::string startDate_;
    //Pole przechowujące prowizję kredytu
    std::string commision_;
    //Pole przechowujące oprocentowanie kredytu
    std::string interest_;
    //Pole przechowujące wartość miesięcznej raty
    std::string installment_;
    //Wektor wartości typu double przechowujący ratę kapitałową
    std::vector<double> capital_payments;
    //Wektor wartości typu double przechowujący ratę odsetkową
    std::vector<double> interest_payments;
    //Wektor wartości typu double przechowujący raty miesięczne
    std::vector<double> installments;
    //Wektor wartości typu double przechowujący saldo zadłużenia
    std::vector<double> balances;
    //Wektor wartości typu std::string przechowujący daty następnych rat
    std::vector<std::string> dates;
    //Wskaźnik na obiekt typu Client
    Client *client_;
    //Wskaźnik na obiekt typu AccountManager
    AccountManager *accManager;
public:
    //Konstruktor
    //@param client wskaźnik na obiekt klasy Client
    CreditSchedule(Client *client);
    //Destruktor
    ~CreditSchedule();
    //Funkcja wczytująca harmonogram spłaty kredytu z pliku tekstowego
    //@param acc_number przechowuje numer konta kredytowego
    bool readSchedule(const std::string acc_number);
    //Funkcja aktualizująca pole wyświetlające saldo zadłużenia
    //@param amount przechowuje kwotę
    //@param acc_number przechowuje numer konta kredytowego
    void updateBalance(double amount, const std::string acc_number);
    //Funkcja przechodząca do następnej wartości w wektorze capital_payments
    double nextCapitalPayment();
    //Funkcja przechodząca do następnej wartości w wektorze interest_payments
    double nextInterestPayment();
    //Funkcja przechodząca do następnej wartości w wektorze balances
    double nextBalance();
    //Funkcja przechodząca do następnej wartości w wektorze dates
    std::string nextDate();
    //Funkcja zwracająca wartość pola financialPeriod_
    std::string getFinancialPeriod() const;
    //Funkcja zwracająca wartośc pola investmentValue_
    std::string getInvestmentValue() const;
    //Funkcja zwracająca wartość pola startDate_
    std::string getStartDate() const;
    //Funkcja zwracająca wartość pola commision_
    std::string getCommision() const;
    //Funkcja zwracająca wartość pola inerest_
    std::string getInterest() const;
    //Funkcja zwracająca wartość pola installment_
    std::string getInstallment() const;
    //Funkcja zwracająca wektor interest_payments
    std::vector<double> getInterestPayments() const;
    //Funkcja zwracająca wektor capital_payments
    std::vector<double> getCapitalPayments() const;
    //Funkcja zwracająca wektor dates
    std::vector<std::string> getDates() const;
    //Funkcja zwracająca wektor balances
    std::vector<double> getBalances() const;
};

#endif // CREDITSCHEDULE_H
