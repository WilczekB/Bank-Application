
#include "includes.h"
#include "intransaction.h"
#include "outtransaction.h"
#include "bankaccount.h"

/*
 * Konstruktor
 * Konstruktor przyjmuje wskaźnik do obiektu typu Client jako argument
 * Następnie przypisuje ten wskaźnik do prywatnego pola client_
 */
AccountManager::AccountManager(Client* client) : client_(client)
{
    this->readAccounts("C:\\Users\\Bartek\\Desktop\\BankApp\\accounts.txt");
}

/*
 * Destruktor
 * Zwalnia pamięć dla wszystkich kont oraz klienta
 */
AccountManager::~AccountManager()
{
    //Iteracja po wektorze accounts, przechowującego wskaźniki
    //do wszystkich kont
    for(auto account : accounts)
    {
        //Zwolnienie pamięcie zajmowanej przez obiekt typu BankAccount
        delete account;
    }

    //Zwolnienie pamięci zajmowanej przez obiekt typu Client
    delete client_;
}

/*
 * Funkcja realizująca wysyłanie transakcji pomiędzy kontami.
 */
bool AccountManager::sendTransaction(const std::string& accountNumber, const std::string& reciver, const std::string& senderAccNumber, double amount, const std::string& title)
{
    //Znajdź konto nadawcy i odbiorcy
    BankAccount* senderAcc = findAccount(senderAccNumber);
    BankAccount* reciverAcc = findAccount(accountNumber);

    //Warunek if() sprawdzający, czy konta nadawcy i odbiorcy
    //istnieją oraz czy kwota transakcji jest większa od zera
    if(!senderAcc || !reciverAcc || amount<=0) return false;

    //Sprawdzenie, czy kwota transakcji nie jest większa niż
    //dostępne środki na koncie nadawcy
    double sum = senderAcc->getBalance();
    if(sum < amount) return false;

    //Utworzenie obiektów transakcji wychodzącej i przychodzącej
    OutTransaction* outTransaction = new OutTransaction(amount, reciver, title, senderAcc);
    InTransaction* inTransaction = new InTransaction(amount, client_->getFullname(), senderAcc->getAccountNumber(), title);

    //Dodanie transakcji do odpowiednich kont
    senderAcc->addTransaction(outTransaction);
    reciverAcc->addTransaction(inTransaction);

    //Dodanie kwoty do konta odbiorcy
    //Pobranie kwoty z konta nadawcys
    takeMoney(amount, senderAcc);
    addMoney(amount, reciverAcc);

    //Zwrócenie wartości true
    //w przypadku prawidłowego przeprowadzenia transakcji
    return true;
}

/*
 * Funkcja dodająca daną kwotę do konta.
 */
void AccountManager::addMoney(double amount, BankAccount* account)
{
    //Pobierz aktualne saldo konta
    double sum = account->getBalance();

    //Dodaj kwotę do aktualnego salda
    sum += amount;

    //Ustaw nowe saldo konta
    account->setBalance(sum);
}

/*
 * Funkcja pobierająca daną kwotę z konta.
 */
void AccountManager::takeMoney(double amount, BankAccount* account)
{
    //Pobierz aktualne saldo konta
    double sum = account->getBalance();

    //Odejmij kwotę od aktualnego salda
    sum -= amount;

    //Ustaw nowe saldo konta
    account->setBalance(sum);
}


/*
*   Funkcja obliczająca wydatki na koncie.
*/
double AccountManager::calcualteExpanse()
{
    //Inicjalizacja zmiennej przechowującej sumę wydatków
    double expenses = 0.0;

    //Pętla for() iterująca po kontach w vectorze accounts
    for(BankAccount* account : accounts)
    {
        //Pętla for() iterująca po transakcjach na koncie
        for(Transaction* transaction : account->getTransactions())
        {
            //Sprawdzenie czy transakcja jest transakcją wychodzącą
            OutTransaction* outTransaction = dynamic_cast<OutTransaction*>(transaction);
            if(outTransaction != nullptr)
            {
                //Dodanie kwoty transakcji do sumy wydatków
                expenses += outTransaction->getAmount();
            }
        }
    }

    //Zwrócenie sumy wydatków
    return expenses;
}

/*
* Funkcja obliczająca bilans między wydatkami, a zyskami
*/
double AccountManager::calculateBalance()
{
    //Inicjalizacja zmiennych przechowujących saldo, zysk i wydatki
    double balance = 0.0;
    double expanse = 0.0;
    double profit = 0.0;

    //Obliczenie wydatków
    //Obliczenie zysku
    expanse = calcualteExpanse();
    profit = calculateProfit();

    //Obliczenie salda jako różnicy zysku i wydatków
    balance = profit - expanse;

    //Zwrócenie salda
    return balance;
}

/*
* Funkcja obliczająca zyski na koncie.
*/
double AccountManager::calculateProfit()
{
    //Inicjalizacja zmiennej przechowującej zysk
    double profit = 0.0;

    //Pętla for() iterująca po kontach w vectorze accounts
    for(BankAccount* accont : accounts)
    {
        //Pętla for() iterująca po transakcjach na koncie
        for(Transaction* transaction : accont->getTransactions())
        {
            //Sprawdzenie czy transakcja jest transakcją przychodzącą
            InTransaction* inTransaction = dynamic_cast<InTransaction*>(transaction);
            if(inTransaction != nullptr)
            {
                //Dodanie kwoty do zysku
                profit += inTransaction->getAmount();
            }
        }
    }

    //Zwrócenie zysku
    return profit;
}

/*
 * Funkcja zapisująca utworzone konta do pliku tekstowego.
 */
void AccountManager::writeAccounts(const std::string file_name)
{

    //Otwieranie pliku wyjściowego
    std::ofstream outputFile(file_name);
    //Sprawdzenie czy plik otworzył się prawidłowo
    if(!outputFile.is_open())
    {
        //Wyrzucenie wyjątku przy błędnym otwarciu pliku
        throw std::runtime_error("Blad otwarcia pliku");
        return;
    }

    //Pętla for() iterująca po kontach w vectorze accounts
    for(BankAccount* account : accounts)
    {
        if(Credit *creditAccount = dynamic_cast<Credit*>(account))
        {
            outputFile << creditAccount->getType() << ' ' <<
                creditAccount->getAccountNumber() << ' ' <<
                creditAccount->getBalance() << ' ' <<
                creditAccount->getOwnerID() << ' ' <<
                creditAccount->getCommision() << ' ' <<
                creditAccount->getFinancialPeriod() << ' ' <<
                creditAccount->getInvestmentValue() << ' ' <<
                creditAccount->getPercentage() << ' ' <<
                creditAccount->getStartDate().toString(Qt::ISODate).toStdString() << ' ';

            writeTransactions("C:\\Users\\Bartek\\Desktop\\BankApp\\transactions.txt", account);

            for(const auto& transaction : creditAccount->getTransactions())
            {
                outputFile << transaction->getId() << ",";
            }

            outputFile << "\n";

        }else if(SavingsAccount *savingsAccount = dynamic_cast<SavingsAccount*>(account)){

            outputFile << savingsAccount->getType() << ' ' <<
                savingsAccount->getAccountNumber() << ' ' <<
                savingsAccount->getBalance() << ' ' <<
                savingsAccount->getOwnerID() << ' ' <<
                savingsAccount->getInterestRate() << ' ' <<
                savingsAccount->getWithdrawalLimit() << ' ';

            writeTransactions("C:\\Users\\Bartek\\Desktop\\BankApp\\transactions.txt", account);

            for(const auto& transaction : savingsAccount->getTransactions())
            {
                outputFile << transaction->getId() << ",";
            }

            outputFile << '\n';
        }


    }

    //Zamknięcie pliku
    outputFile.close();
}

/*
 * Funkcja wczytująca z pliku tekstowego konta.
 */
void AccountManager::readAccounts(const std::string file_name)
{
    //Otwarcie pliku
    std::ifstream inputFile(file_name);
    //Warunek sprawdzający poprawne otwarcie pliku
    if(!inputFile.is_open())
    {
        //Wyrzucenie wyjątku w przypadku braku otwarcia pliku
        throw std::runtime_error("Blad odczytu pliku");
        return;
    }

    std::string line;

    //odczytywanie w pętli while() linia po linii z pliku
    while(std::getline(inputFile, line))
    {
        //utworzenie strumienia istringstream, służący do parsowania ciągu znaków
        std::istringstream iss(line);
        std::string account_type;

        //wczytanie ciągu znaków określającego typ konta
        iss >> account_type;

        //warunek if() sprawdzający z jakim typem konta mamy do czynienia
        if(account_type == "Kredyt")
        {

            //deklaracja zmiennych
            std::string account_number, ownerID;
            double investment_value_, percentage_, commision_, balance_;
            int financial_period_;
            std::string start_date_string;

            //Wczytanie danych konta kredytowego
            iss >> account_number >> balance_ >> ownerID >> investment_value_ >> percentage_ >> commision_ >> financial_period_
                >> start_date_string;

            //Konwersja daty z formatu string do QDate
            QDate start_date_ = QDate::fromString(QString::fromStdString(start_date_string), "yyyy-MM-dd");

            //Utworzenie obiektu credit
            Credit* credit = new Credit(account_number, balance_, start_date_, financial_period_, investment_value_, percentage_, commision_, ownerID);

            //Rzutowanie obiektu credit na wskaźnik na klasę BankAccount
            BankAccount* account = dynamic_cast<BankAccount*>(credit);

            //Przypisanie do konta transakcji zapisanych w pliku tekstowym
            readTransactions("C:\\Users\\Bartek\\Desktop\\BankApp\\transactions.txt", account);

            //Dodanie konta do vectora accounts
            accounts.push_back(account);

        }else if(account_type == "Konto"){

            //Deklaracja zmiennych dla konta oszczędnościowego
            double interest_rate_, balance_;
            int withdrawal_limit_;
            std::string account_number, ownerID;

            //Wczytanie danych konta oszczędnościowego
            iss >> account_number >> balance_ >> ownerID >> interest_rate_ >> withdrawal_limit_ ;

            //Utworzenie obiektu konta oszczędnościowego
            SavingsAccount* savings_account = new SavingsAccount(account_number, balance_, interest_rate_, withdrawal_limit_, ownerID);

            //Rzutowanie obiektu konta oszczędnościowego na wskaźnik na klasę BankAccount
            BankAccount* account = dynamic_cast<BankAccount*>(savings_account);

            //Przypisanie do konta transakcji zapisanych w pliku tekstowym
            readTransactions("C:\\Users\\Bartek\\Desktop\\BankApp\\transactions.txt", account);

            //Dodanie konta do vectora accounts
            accounts.push_back(account);

        }else{
            //Obsługa nieznanych typów konta
            std::cerr << "Bledny typ konta: " << account_type << std::endl;
        }

    }

    //Zamknięcie pliku
    inputFile.close();
}

/*
 * Funkcja umożliwiająca znalezienie poszukiwanego konta.
 */
BankAccount* AccountManager::findAccount(const std::string& accountNumber) const
{
    //pętla for() iterująca po kontach w vectorze accounts
    for(BankAccount* account : accounts)
    {
        //warunek if() sprawdzający czy wartość argumentu account_number obiektu jest zgodny z poszukiwanym
        if(account->getAccountNumber() == accountNumber)
        {
            //zwrócenie poszukiwanego obiektu
            return account;
        }
    }
    //zwrócenie wartości nullptr w przypadku niepowodzenia
    return nullptr;
}

/*
 * Funkcja dodająca nowe konto.
 */
void AccountManager::addAccount(BankAccount *account)
{
    //dodanie konta do vectora accounts
    accounts.push_back(account);
}

/*
 * Funkcja usuwająca konto.
 */
bool AccountManager::removeAccount(BankAccount *account)
{
    //szukanie iteratora na konto o podanym adresie w vectorze accounts
    auto it = std::find(accounts.begin(), accounts.end(), account);
    //warunek sprawdzający, czy znaleziono konto
    if(it != accounts.end())
    {
        //usunięcie konta z vectora
        accounts.erase(it);
        //zwrócenie wartości true
        return true;
    }
    //zwrócenie wartości false w przypadku niepowodzenia w usunięciu konta
    return false;
}

/*
 * Funkcja zwracająca wszystkie konta należące do danego klienta po jego numerze pesel
 */
std::vector<BankAccount*> AccountManager::findByOwner(const std::string& idOwner) const
{
    //Inicjalizacja vectora, który będzie przechowywał wszystkie konta klienta
    std::vector<BankAccount*> ownerAccounts;

    //Pętla for() iterująca po kontach w vectorze accounts
    for(BankAccount *account : accounts)
    {
        //Warunek sprawdzający czy pesel właściciela konta odpowiada podanemu idOwner
        if(account->getOwnerID() == idOwner)
        {
            //W przypadku znalezienia pasującego konta, dodanie go do vectora
            ownerAccounts.push_back(account);
        }
    }

    //Zwrócenie vectora z wszystkimi kontami klienta
    return ownerAccounts;
}

void AccountManager::writeTransactions(const std::string file_name, BankAccount *account)
{

    //Otwieranie pliku wyjściowego
    std::ofstream outputFile(file_name);

    //Sprawdzenie czy plik otworzył się prawidłowo
    if(!outputFile.is_open())
    {
        //Wyrzucenie wyjątku przy błędnym otwarciu pliku
        throw std::runtime_error("Blad otwarcia pliku");
        return;
    }

    //Przejście po każdej z transakcji
    for(const Transaction *transaction : account->getTransactions())
    {
        if(const InTransaction *inTransaction = dynamic_cast<const InTransaction*>(transaction))
        {

            outputFile << inTransaction->getInfo() << '\n';

        }else if(const OutTransaction *outTransaction = dynamic_cast<const OutTransaction*>(transaction)){

            outputFile << outTransaction->getInfo() << '\n';

        }
    }

    //Zamknięcie pliku wyjściowego
    outputFile.close();

}

void AccountManager::readTransactions(const std::string file_name, BankAccount *account)
{
    //Otwarcie pliku
    std::ifstream inputFile(file_name);

    //Warunek sprawdzający poprawne otwarcie pliku
    if(!inputFile.is_open())
    {
        //Wyrzucenie wyjątku w przypadku braku otwarcia pliku
        throw std::runtime_error("Blad odczytu pliku");
        return;
    }

    std::string line;

    std::vector<int> accountIds = account->getTransactionsId();

    while(std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string transaction_type;
        int id;

        iss >> id;

        for(int accID : accountIds)
        {
            if(id == accID)
            {

                iss >> transaction_type;

                if(transaction_type == "IN")
                {

                    std::string sender, title, senderAccountNumber;
                    double amount;

                    iss >> amount >> title >> sender >> senderAccountNumber;

                    InTransaction *inTransaction = new InTransaction(amount, sender, senderAccountNumber, title);

                    account->addTransaction(dynamic_cast<Transaction*>(inTransaction));

                }else if(transaction_type == "OUT"){

                    double amount;
                    std::string reciver, title;

                    iss >> amount >> title >> reciver;

                    OutTransaction *outTransaction = new OutTransaction(amount, reciver, title, account);

                    account->addTransaction(dynamic_cast<Transaction*>(outTransaction));

                }

            }
        }

    }

}

std::string AccountManager::randomizeAmount()
{
    //Generowanie losowego numeru konta
    std::string amount;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,9);
    for(int i=0; i < 3; i++)
    {
        amount += std::to_string(dis(gen));
    }

    return amount;
}
