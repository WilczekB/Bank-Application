#include "mycreditwindow.h"
#include "ui_mycreditwindow.h"

/*
 * Konstruktor
 */
MyCreditWindow::MyCreditWindow(QWidget *parent, Client *client) :
    QDialog(parent),
    ui(new Ui::MyCreditWindow)
{
    //Inicjalizacja interfejsu użytkownika dla okna danych klienta
    ui->setupUi(this);

    //Przypisanie wskaźnika na obiekt client do pola client_
    client_ = client;

    //Przypisanie wskaźnika na obiekt AccountManager klienta do pola accountManager_
    accManager = client->getAccountManager();

    //Utworzenie nowego obiektu creditSchedule
    creditSchedule = new CreditSchedule(client);

    //Wywołanie funkcji setComboBox()
    setComboBox();
}

/*
 * Destruktor
 */
MyCreditWindow::~MyCreditWindow()
{
    //Usunięcie obiektów
    delete client_;
    delete accManager;
    delete ui;
}

/*
 * Funkcja dokonująca spłaty miesięcznej raty
 */
void MyCreditWindow::on_updateButton_clicked()
{

    //Pobierz następną płatność kapitałową z harmonogramu kredytowego
    double capitalPayment = creditSchedule->nextCapitalPayment();

    // Pobierz następną płatność odsetkową z harmonogramu kredytowego
    double interestPayment = creditSchedule->nextInterestPayment();

    // Pobierz następną datę z harmonogramu kredytowego
    std::string date = creditSchedule->nextDate();

    // Pobierz następne saldo z harmonogramu kredytowego
    double balance = creditSchedule->nextBalance();

    // Pobierz numer konta kredytowego z interfejsu użytkownika
    std::string account_number = ui->creditNumberBox->currentText().toStdString();

    // Zaktualizuj saldo konta na interfejsie
    updateBalance(balance);

    // Zaktualizuj wyświetlaną datę na interfejsie
    updateDate(date);

    // Zaktualizuj wyświetlaną płatność kapitałową na interfejsie
    updateCapitalPayment(capitalPayment);

    // Zaktualizuj wyświetlaną płatność odsetkową na interfejsie
    updateInterestPayment(interestPayment);

    // Zaktualizuj saldo konta w harmonogramie kredytowym
    creditSchedule->updateBalance(interestPayment, account_number);

}

/*
 * Funkcja zamykająca interfejs
 */
void MyCreditWindow::on_exitButton_clicked()
{

    //Wywołanie metody ukrycia okna z harmongoramem spłaty kredytu klienta
    hide();

}

/*
 * Funkcja ustawiająaca i zarządzająca danymi
 */
void MyCreditWindow::setData(const std::string accNumber)
{

    //Ustaw pola tekstowe jako tylko odczytu
    setToReadOnly();

    //Sprawdź czy udało się odczytać harmonogram kredytowy dla danego numeru konta
    if(!creditSchedule->readSchedule(accNumber)){

        // Wyświetl komunikat informacyjny o braku kredytu
        QMessageBox::information(this, "Brak kredytu", "Nie posiadasz żadnego kredytu.");
        // Ukryj okno
        hide();

    }

    //Ustawienie początkowego tekstu w polach na interfejsie użytkownika
    setInitialText();

}

/*
 * Funkcja wypełniająca QComboBox numerami kont kredytowych
 */
void MyCreditWindow::setComboBox()
{
    //Pobierz listę kredytów klienta na podstawie jego numeru PESEL
    std::vector<BankAccount*> clientCredits = accManager->findByOwner(client_->getPesel());

    //Iteruj przez każde konto w liście
    for(BankAccount *account : clientCredits)
    {
        //Sprawdź czy konto jest typu kredytowego za pomocą dynamicznego rzutowania
        if(Credit *creditAccount = dynamic_cast<Credit*>(account))
        {
            //Dodaj numer konta kredytowego do ComboBox na interfejsie użytkownika
            ui->creditNumberBox->addItem(QString::fromStdString(creditAccount->getAccountNumber()));
        }
    }
}

/*
 * Funkcja aktualizująca dane w zależności od wybranego numeru konta kredytowego
 */
void MyCreditWindow::on_creditNumberBox_currentTextChanged(const QString &arg1)
{
    //Pobierz konto bankowe na podstawie wybranego numeru konta kredytowego
    BankAccount *account = accManager->findAccount(arg1.toStdString());

    //Ustaw dane na interfejsie użytkownika dla wybranego konta
    setData(account->getAccountNumber());
}

/*
 * Funkcja ustawiająca dane tylko do odczytu
 */
void MyCreditWindow::setToReadOnly()
{
    //Ustawienie pól tylko do odczytu
    ui->commisionEdit->setReadOnly(true);
    ui->financialPeriodEdit->setReadOnly(true);
    ui->installmentEdit->setReadOnly(true);
    ui->interestEdit->setReadOnly(true);
    ui->investmentValueEdit->setReadOnly(true);
    ui->capitalAmountEdit->setReadOnly(true);
    ui->debtBalanceEdit->setReadOnly(true);
    ui->startDateEdit->setReadOnly(true);
    ui->interestAmountEdit->setReadOnly(true);
    ui->nextDateEdit->setReadOnly(true);
}

/*
 * Funkcja ustawiająca początkowe dane
 */
void MyCreditWindow::setInitialText()
{

    //Przypisanie pierwszych wartości do pól tekstowych
    ui->commisionEdit->setText(QString::fromStdString(creditSchedule->getCommision()));
    ui->financialPeriodEdit->setText(QString::fromStdString(creditSchedule->getFinancialPeriod()));
    ui->installmentEdit->setText(QString::fromStdString(creditSchedule->getInstallment()));
    ui->interestEdit->setText(QString::fromStdString(creditSchedule->getInterest()));
    ui->investmentValueEdit->setText(QString::fromStdString(creditSchedule->getInvestmentValue()));
    ui->startDateEdit->setText(QString::fromStdString(creditSchedule->getStartDate()));

    ui->capitalAmountEdit->setText(QString::number(creditSchedule->getCapitalPayments().front()));
    ui->interestAmountEdit->setText(QString::number(creditSchedule->getInterestPayments().front()));
    ui->debtBalanceEdit->setText(QString::number(creditSchedule->getBalances().front()));
    ui->nextDateEdit->setText(QString::fromStdString(creditSchedule->getDates().front()));

}

/*
 * Funkcja aktualizująca wartość salda
 */
void MyCreditWindow::updateBalance(double balance)
{
    //Ustawienie nowej wartości salda do pola tekstowego
    ui->debtBalanceEdit->setText(QString::number(balance));
}

/*
 * Funkcja aktualizująca wartość raty kapitałowej
 */
void MyCreditWindow::updateCapitalPayment(double capital)
{
    //Ustawienie nowej wartości raty kapitałowej do pola tekstowego
    ui->capitalAmountEdit->setText(QString::number(capital));
}

/*
 * Funkcja aktualizująca wartość raty odsetkowej
 */
void MyCreditWindow::updateInterestPayment(double interest)
{
    //Ustawienie nowej wartości raty odsetkowej do pola tekstowego
    ui->interestAmountEdit->setText(QString::number(interest));
}

/*
 * Funkcja aktualizująca datę spłaty raty kredytowej
 */
void MyCreditWindow::updateDate(const std::string date)
{
    //Ustawienie nowej wartości daty spłaty raty kredytowej do pola tekstowego
    ui->nextDateEdit->setText(QString::fromStdString(date));
}
