#include "accountswindow.h"
#include "transactionwindow.h"
#include "ui_accountswindow.h"

/*
 * Konstruktor
 */
AccountsWindow::AccountsWindow(QWidget *parent, Client *client) :
    QDialog(parent),
    ui(new Ui::AccountsWindow)
{
    //Inicjalizacja interfejsu użytkownika dla okna z kontami bankowymi klienta
    ui->setupUi(this);

    //Przypisanie wskaźnika na obiekt client do pola client_
    client_ = client;

    //Przypisanie wskaźnika na obiekt AccountManager klienta do pola accountManager_
    accountManager_ = client->getAccountManager();

    //Wywołanie metod do wyświetlenia danych odnośnie kont i przeprowadzonych transakcji
    setSelectionBox();

}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu AccountManager, Client, TransactionWindow i Ui
 */
AccountsWindow::~AccountsWindow()
{
    delete accountManager_;
    delete client_;
    delete transactionWindow;
    delete myCreditWindow;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku sendTransactionButton powoduje otwarcie interfejsu okna do wysyłania transakcji
 */
void AccountsWindow::on_sendTransactionButton_clicked()
{
    //Znalezenie akttualnie wybranego konta po numerze
    BankAccount *account = accountManager_->findAccount(ui->accountsComboBox->currentText().toStdString());

    //Utworzenie nowego obiektu TransactionWindow, przekazując wskaźnik na obiekt rodzica
    transactionWindow = new TransactionWindow(this, accountManager_, account, client_);

    //Wyświetlenie okna do wysyłania transakcji
    transactionWindow->show();

}

/*
 * Slot, który po wciśnięciu przycisku goBackButton powoduje zamknięcie okna z kontami bankowymi klienta
 */
void AccountsWindow::on_goBackButton_clicked()
{
    //Wywołanie metody ukrycia okna z kontami bankowymi klienta
    hide();
}

/*
 * Funkcja wyświetlająca historię transakcji danego konta bankowego
 */
void AccountsWindow::setTransactionsData(const std::string acc_number)
{
    //Wyszukanie konta bankowego przypisanego do klienta na podstawie numeru pesel
    BankAccount* account = accountManager_->findAccount(acc_number);

    //Wywołanie metody showTransactions(), która zwraca wszystkie transakcje dla danego konta
    //Konwersja historii transakcji na typ QString
    QString description = account->showTransactions();

    //Wyczysczenie pola edycji
    ui->plainTextEdit->clear();

    //Ustawienie kolumn w polu edycji
    ui->plainTextEdit->setPlainText("Id: \tTyp: \tKwota: \tTytul: \tOd:");

    //Dodanie historii transakcji do pola edycji
    ui->plainTextEdit->appendPlainText(description);

}

void AccountsWindow::setSelectionBox()
{
    std::vector<BankAccount*> clientAccounts = accountManager_->findByOwner(client_->getPesel());

    //Iteracja po każdym z kont
    for(const auto& account : clientAccounts)
    {
        //Dodanie numeru konta do ComboBox
        ui->accountsComboBox->addItem(QString::fromStdString(account->getAccountNumber()));
    }
}

/*
 * Funkcja ustawiająca saldo oraz historię transakcji na podstawie wybranego konta
 */
void AccountsWindow::on_accountsComboBox_currentTextChanged(const QString &arg1)
{
    //Znalezenie akttualnie wybranego konta po numerze
    BankAccount* account = accountManager_->findAccount(arg1.toStdString());

    //Ustawienie wartości salda konta
    ui->sumLineEdit->setText(QString::number(account->getBalance()) + " zł");

    //Wywołanie funkcji wyświetlającej historię transakcji
    setTransactionsData(arg1.toStdString());
}


void AccountsWindow::on_myCreditButton_clicked()
{

    myCreditWindow = new MyCreditWindow(this, client_);

    myCreditWindow->show();

}

