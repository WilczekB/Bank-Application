
#include "creditschedule.h"

/*
 * Konstruktor
 */
CreditSchedule::CreditSchedule(Client *client)
{
    //Przypisanie wskaźnika na obiekt client do pola client_
    client_ = client;

    //Przypisanie wskaźnika na obiekt AccountManager klienta do pola accountManager_
    accManager = client->getAccountManager();
}

/*
 * Destruktor
 */
CreditSchedule::~CreditSchedule()
{
    //Zwolnienie pamięci zajmowanej przez obiekty client_ i accManager
    delete client_;
    delete accManager;
}

/*
 * Funkcja wczytująca harmonogram spłaty kredytu z pliku tekstowego
 */
bool CreditSchedule::readSchedule(const std::string acc_number)
{
    //Scieżka do pliku tekstowego
    std::ifstream inputFile("C:\\Users\\Bartek\\Desktop\\BankApp\\harmonogram_" + acc_number + ".txt");

    //Warunek sprawdzający poprawne otwarcie pliku
    if(!inputFile.is_open())
    {
        //Wyrzucenie wyjątku w przypadku braku otwarcia pliku
        throw std::runtime_error("Blad odczytu pliku");
        return false;
    }

    std::string line;

    while(std::getline(inputFile, line))
    {
        //Sprawdzenie czy w linii tekstu znajduje się fraza "Data rozpoczęcia:"
        if(line.find("Data rozpoczecia:") != std::string::npos)
        {
            //Odczytanie daty rozpoczęcia
            startDate_ = line.substr(line.find(":") + 2);

        //Sprawdzenie czy w linii tekstu znajduje się fraza "Okres finansowania:"
        }else if(line.find("Okres finansowania:") != std::string::npos){

            //Odczytanie okresu finansowania
            financialPeriod_ = line.substr(line.find(":") + 2);

        //Sprawdzenie czy w linii tekstu znajduje się fraza "Wartość inwestycji:"
        }else if(line.find("Wartosc inwestycji:") != std::string::npos){

            //Odczytanie wartości inwestycji
            investmentValue_ = line.substr(line.find(":") + 2);

        //Sprawdzenie czy w linii tekstu znajduje się fraza "Oprocentowanie roczne:"
        }else if(line.find("Oprecentowanie roczne:") != std::string::npos){

            //Odczytanie oprocentowania rocznego
            interest_ = line.substr(line.find(":") + 2);

        //Sprawdzenie czy w linii tekstu znajduje się fraza "Prowizja:"
        }else if(line.find("Prowizja:") != std::string::npos){

            //Odczytanie prowizji
            commision_ = line.substr(line.find(":") + 2);

        //Sprawdzenie czy w linii tekstu znajduje się fraza "Miesięczna rata:"
        }else if(line.find("Miesięczna rata:") != std::string::npos){

            //Odczytanie miesięcznej raty
            installment_ = line.substr(line.find(":") + 2);

        //Sprawdzenie czy w linii tekstu znajduje się fraza "Haromonogram splat:"
        }else if(line.find("Harmonogram splat:") != std::string::npos){

            std::getline(inputFile, line);

            while(std::getline(inputFile, line)){

                //Odczytanie daty spłaty raty
                std::string date = line.substr(0, line.find("\t"));
                //Dodanie wartości do vectora dates
                dates.push_back(date);

                line = line.substr(line.find("\t") + 1);

                //Odczytanie kwoty kapitału
                double capitalAmount = std::stod(line.substr(0, line.find("\t")));
                //Dodanie wartości do vectora capital_payments
                capital_payments.push_back(capitalAmount);

                line = line.substr(line.find("\t") + 1);

                //Odczytanie kwoty odsetek
                double interestAmount = std::stod(line.substr(0, line.find("\t")));
                //Dodanie wartości do vectora interest_payments
                interest_payments.push_back(interestAmount);

                line = line.substr(line.find("\t") + 1);

                //Odczytanie kwoty raty
                double installmentAmount = std::stod(line.substr(0, line.find("\t")));
                //Dodanie wartości do vectora
                installments.push_back(installmentAmount);

                line = line.substr(line.find("\t") + 1);

                //Odczytanie salda
                double balance = std::stod(line.substr(0, line.find("\t")));
                //Dodanie wartości do vectora balances
                balances.push_back(balance);

            }

        }
    }

    //Zamknięcie pliku
    inputFile.close();

    //Zwrócenie wartości true w przypadku poprawnego odczytu harmonogramu
    return true;
}

/*
 * Funkcja zwracająca wartość pola commision
 */
std::string CreditSchedule::getCommision() const
{
    return commision_;
}

/*
 * Funkcja zwracająca wartość pola financialPeriod_
 */
std::string CreditSchedule::getFinancialPeriod() const
{
    return financialPeriod_;
}

/*
 * Funkcja zwracająca wartość pola installment_
 */
std::string CreditSchedule::getInstallment() const
{
    return installment_;
}

/*
 * Funkcja zwracająca wartość pola interest_
 */
std::string CreditSchedule::getInterest() const
{
    return interest_;
}

/*
 * Funkcja zwracająca wartość pola startDate_
 */
std::string CreditSchedule::getStartDate() const
{
    return startDate_;
}

/*
 * Funkcja zwracająca wartość pola investmentValue_
 */
std::string CreditSchedule::getInvestmentValue() const
{
    return investmentValue_;
}

/*
 * Funkcja przechodząca do następnej wartości w vectorze capital_payments i zwracająca tę wartość
 */
double CreditSchedule::nextCapitalPayment()
{
    //Statyczna zmienna przechowująca indeks następnej płatności
    static int index = 0;

    //Zwiększenie indeksu o 1
    index++;

    //Sprawdzenie, czy istnieje kolejna płatność kapitałowa
    if(index < capital_payments.size()){

        //Przechowanie wartości następnej płatności kapitałowej
        double temp = capital_payments[index];
        //Przypisanie poprzedniej wartości płatności do aktulnego indeksu
        capital_payments[index] = capital_payments[index - 1];
        //Przypisanie przechowanej wartości jako poprzedniej płatności
        capital_payments[index - 1] = temp;
        //Zwrócenie poprzedniej płatności kapitałowej
        return capital_payments[index-1];
    }

    //Zwrócenie 0, jeśli nie ma kolejnych płatności
    return 0;
}

/*
 * Funkcja przechodząca do następnej wartości w vectorze interest_payments i zwracająca tę wartość
 */
double CreditSchedule::nextInterestPayment()
{
    //Statyczna zmienna przechowująca indeks następnej płatności
    static int index = 0;

    //Zwiększenie indeksu o 1
    index++;

    //Sprawdzenie, czy istnieje kolejna płatność odsetkowa
    if(index < interest_payments.size()){

        //Przechowanie wartości następnej płatności odsetkowej
        double temp = interest_payments[index];
        //Przypisanie poprzedniej wartości płatności do aktulnego indeksu
        interest_payments[index] = interest_payments[index - 1];
        //Przypisanie przechowanej wartości jako poprzedniej płatności
        interest_payments[index - 1] = temp;
        //Zwrócenie poprzedniej płatności odsetkowej
        return interest_payments[index-1];
    }

    //Zwrócenie 0, jeśli nie ma kolejnych płatności
    return 0;
}

/*
 * Funkcja przechodząca do następnej wartości w vectorze dates i zwracająca tę wartość
 */
std::string CreditSchedule::nextDate()
{
    //Statyczna zmienna przechowująca indeks następnej daty
    static int index = 0;

    //Zwiększenie indeksu o 1
    index++;

    //Sprawdzenie, czy istnieje kolejna data
    if(index < dates.size()){

        //Przechowanie wartości następnej daty
        std::string temp = dates[index];
        //Przypisanie poprzedniej wartości daty do aktulnego indeksu
        dates[index] = dates[index - 1];
        //Przypisanie przechowanej wartości jako poprzedniej daty
        dates[index - 1] = temp;
        //Zwrócenie poprzedniej daty
        return dates[index-1];

    }

    //Zwrócenie wartości nullptr, jeśli nie ma kolejnej daty
    return nullptr;
}

/*
 * Funkcja przechodząca do następnej wartości w vectorze balances i zwracająca tę wartość
 */
double CreditSchedule::nextBalance()
{
    //Statyczna zmienna przechowująca indeks następnego salda
    static int index = 0;

    //Zwiększenie indeksu o 1
    index++;

    //Sprawdzenie, czy istnieje kolejne saldo
    if(index < balances.size()){

        //Przechowanie wartości następnego salda
        double temp = balances[index];
        //Przypisanie poprzedniej wartości salda do aktulnego indeksu
        balances[index] = balances[index - 1];
        //Przypisanie przechowanej wartości jako poprzedniego salda
        balances[index - 1] = temp;
        //Zwrócenie poprzedniego salda
        return balances[index - 1];

    }

    //Zwrócenie 0, jeśli nie ma kolejnego salda
    return 0;
}

/*
 * Funkcja aktualizująca wartość salda po opłaceniu raty kredytu
 */
void CreditSchedule::updateBalance(double amount, const std::string acc_number)
{
    //Znajdź konto bankowe na podstawie numeru konta
    BankAccount *account = accManager->findAccount(acc_number);

    //Zaktualizuj saldo konta, pobierając kwotę amount z konta za pomocą obiektu accManager
    accManager->takeMoney(amount, account);
}

/*
 * Funkcja zwracająca vector capital_payments
 */
std::vector<double> CreditSchedule::getCapitalPayments() const
{
    return capital_payments;
}

/*
 * Funkcja zwracająca vector interest_payments
 */
std::vector<double> CreditSchedule::getInterestPayments() const
{
    return interest_payments;
}

/*
 * Funkcja zwracająca vector dates
 */
std::vector<std::string> CreditSchedule::getDates() const
{
    return dates;
}

/*
 * Funkcja zwracająca vector balances
 */
std::vector<double> CreditSchedule::getBalances() const
{
    return balances;
}
