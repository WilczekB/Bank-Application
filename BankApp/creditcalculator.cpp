
#include "creditcalculator.h"
#include "client.h"

/*
 * Konstruktor
 */
CreditCalculator::CreditCalculator(Credit* credit)
    : credit_(credit)
{

}

/*
 * Destruktor
 */
CreditCalculator::~CreditCalculator()
{
    //Zwolnienie pamięci zajmowanej przez obiekt Credit
    delete credit_;
}

void CreditCalculator::calculate()
{
    //Nazwa pliku do zapisu harmonogramu spłat kredytu
    std::string file_name = "C:\\Users\\Bartek\\Desktop\\BankApp\\harmonogram_" + credit_->getAccountNumber() + ".txt";

    //Otwarcie pliku do zapisu
    std::ofstream outputFile(file_name);

    //Sprawdzenie czy plik został otwarty prawidłowo
    if(!outputFile.is_open())
    {
        //Wyrzucenie wyjątku w przypadku braku możliwości otwarcia pliku
        throw std::runtime_error("Blad otwarcia pliku");
    }

    std::cout << credit_->getCommision();

    //Zapis informacji o harmonogramie spłat kredytu do pliku tekstowego
    outputFile << "Harmonogram splat kredytu" << "\n";
    outputFile << "Data rozpoczecia: " << credit_->getStartDate().toString("dd.MM.yyyy").toStdString() << '\n';
    outputFile << "Okres finansowania: " << credit_->getFinancialPeriod() << " miesiecy" << '\n';
    outputFile << "Wartosc inwestycji: " << std::fixed << std::setprecision(2) << credit_->getInvestmentValue() << '\n';
    outputFile << "Oprecentowanie roczne: " << std::fixed << std::setprecision(2) << credit_->getPercentage() << "%" << '\n';
    outputFile << "Prowizja: " << std::fixed << std::setprecision(2) << credit_->getCommision() << "%" << '\n';

    //Obliczanie potrzebnych wartości kredytu
    double investmentValue = credit_->getInvestmentValue();
    double percentage = credit_->getPercentage() / 12 / 100;
    double comission = credit_->getCommision() / 100;
    int financialPeriod = credit_->getFinancialPeriod();

    double monthlyPayment = (investmentValue * percentage) / (1 - pow(1+percentage, -financialPeriod));
    double totalComission = investmentValue + comission;

    //Zapisanie obliczanych wartości kredytu do pliku tekstowego
    outputFile << "Miesięczna rata: " << std::fixed << std::setprecision(2) << monthlyPayment << '\n';
    outputFile << "Calkowita prowizja: " << std::fixed << std::setprecision(2) << totalComission << '\n';

    outputFile << "Harmonogram splat: " << '\n';
    outputFile << "Data\t\tKwota kapitalu\tKwota odsetek\tRata miesieczna\tSaldo zadluzenia" << '\n';

    //Inicjalizacja vecctorów przechowujących wartości dla każdego okresu spłaty
    std::vector<double> capital_payments;
    std::vector<double> interest_payments;
    std::vector<double> monthly_payments;
    std::vector<double> balances;

    //Inicjalizacja początkowego salda zadłużenia
    double balance = investmentValue;

    //Inicjalizacja daty rozpoczęcia spłaty
    QDate date = credit_->getStartDate();

    for(int i=0; i < financialPeriod; ++i)
    {
        //Wyliczenie kwoty odsetek
        double interest_payment = balance * percentage;
        //Wyliczenie kwoty kapitału
        double capital_payment = monthlyPayment - interest_payment;
        //Wyliczenie salda zadłużenia po spłacie
        double balance_after_payment = balance - capital_payment;

        //Zapisanie informacji o spłacie w danym okresie do pliku tekstowego
        outputFile << date.toString("dd.MM.yyyy").toStdString() << '\t' << std::fixed << std::setprecision(2) << capital_payment << '\t'
                   << interest_payment << '\t' << monthlyPayment << '\t' << balance_after_payment << '\n';

        //Zapisanie wartości do vectorów
        capital_payments.push_back(capital_payment);
        interest_payments.push_back(interest_payment);
        monthly_payments.push_back(interest_payment);
        balances.push_back(balance_after_payment);

        //Aktualizacja salda zadłużenia
        balance = balance_after_payment;

        //Przejście do kolejnego miesiąca
        date = date.addMonths(1);
    }

    //Zamknięcie pliku
    outputFile.close();
}

