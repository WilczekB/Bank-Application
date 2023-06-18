#include "witdrawalwindow.h"
#include "ui_witdrawalwindow.h"

/*
 * Konstruktor
 */
WitdrawalWindow::WitdrawalWindow(QWidget *parent, Client *client) :
    QDialog(parent),
    ui(new Ui::WitdrawalWindow)
{
    //Inicjalizacja interfejsu użytkownika dla okna wypłacania środków
    ui->setupUi(this);

    //Przypisania wskaźnika na obiekt Client do pola client_
    client_ = client;

    //Przypisanie wskaźnika na obiekt AccountManager klienta do pola accountManager_
    accountManager_ = client->getAccountManager();

    //Wywołanie funkcji ustawiającej numery kont klienta
    setAccounts();
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu AccountManager, Client i Ui
 */
WitdrawalWindow::~WitdrawalWindow()
{
    delete accountManager_;
    delete client_;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku withdrawButton realizuje wypłatę środków z konta
 */
void WitdrawalWindow::on_withdrawButton_clicked()
{
    //Pobranie numeru wybranego konta przez użytkownika
    std::string account_number = ui->accountSelectionBox->currentText().toStdString();
    double amount = ui->ammountInput->text().toDouble();

    //Znalezienie poszukiwanego konta po numerze
    BankAccount* account = accountManager_->findAccount(account_number);

    //Wypłacenie zadeklarowanej kwoty z konta
    if(account->withdraw(amount)){
        //W przypadku udanej operacji wyświetlenie komunikatu o wypłaceniu środków
        QMessageBox::information(this, "Wypłacono środki", "Udało się wypłacić zadeklarowaną kwotę.");
    }else{
        //W przypadku niepowodzenia wyświetlenie krytycznego komunikatu o nieudanej próbie wypłacenia środków
        QMessageBox::critical(this, "Błąd podczas wypłacania", "Nie udało się wypłacić zadeklarowanej kwoty.");
    }

    ui->balanceInput->setText(QString::number(account->getBalance()));

    //Wyczyszczenie pola do deklaracji wypłacanej kwoty z konta
    ui->ammountInput->clear();
}

/*
 * Slot, który po wciśnięciu przycisku exitButton realizuje zamknięcie okna wypłacania środków
 */
void WitdrawalWindow::on_exitButton_clicked()
{
    //Ukrycie bieżącego okna wypłacania środków
    hide();
}

/*
 * Funkcja deponująca zadeklarowane środki na koncie
 */
void WitdrawalWindow::on_depositButton_clicked()
{
    //Pobranie numeru wybranego konta przez użytkownika
    std::string account_number = ui->accountSelectionBox->currentText().toStdString();

    //Pobranie zadeklarowanej kwoty przez klienta
    double amount = ui->ammountInput->text().toDouble();

    //Znalezienie poszukiwanego konta po numerze
    BankAccount* account = accountManager_->findAccount(account_number);

    //Zdeponowanie zadeklarowanej kwoty na konto
    account->deposit(amount);

    //Wyświetlenie komunikatu o udanej operacji
    QMessageBox::information(this, "Wpłata środków", "Udało się zdeponować środki na wybrane konto.");

    ui->balanceInput->setText(QString::number(account->getBalance()));

    //Wyczyszczenie pola do deklaracji wypłacanej kwoty z konta
    ui->ammountInput->clear();

}

void WitdrawalWindow::setAccounts()
{
    //Deklaracja vectora, który będzie przechowywał konta należące do danego klienta
    std::vector<BankAccount*> clientAccounts;

    //Znalezienie i dodanie kont należących do danego klienta
    clientAccounts = accountManager_->findByOwner(client_->getPesel());

    //Iteracja po każdym z kont
    for(const auto& account : clientAccounts)
    {
        //Dodanie numeru konta do SelectionBox
        ui->accountSelectionBox->addItem(QString::fromStdString(account->getAccountNumber()));
    }
}

void WitdrawalWindow::on_randAmountButton_clicked()
{
    std::string amount = accountManager_->randomizeAmount();

    ui->ammountInput->setText(QString::fromStdString(amount));
}

void WitdrawalWindow::setBalance(std::string acc_number)
{
    ui->balanceInput->setReadOnly(true);

    BankAccount *account = accountManager_->findAccount(acc_number);

    ui->balanceInput->setText(QString::number(account->getBalance()));
}

void WitdrawalWindow::on_accountSelectionBox_currentTextChanged(const QString &arg1)
{
    std::string accountNumber = arg1.toStdString();
    setBalance(accountNumber);
}

