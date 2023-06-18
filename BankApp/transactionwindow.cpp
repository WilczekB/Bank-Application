#include "transactionwindow.h"
#include "ui_transactionwindow.h"
#include <QInputDialog>
#include <QMessageBox>

/*
 * Konstruktor
 */
TransactionWindow::TransactionWindow(QWidget *parent, AccountManager *accountManager, BankAccount *account, Client *client) :
    QDialog(parent),
    ui(new Ui::TransactionWindow)
{
    //Inicjalizacja obiektu interfejsu użytkownika dla okna wysłania transakcji
    ui->setupUi(this);

    //Przypisanie wartości przekazanych jako argumenty do zmiennych składowych
    accountManager_ = accountManager;
    account_ = account;
    client_ = client;

    //Ustawienie dostępnych kont do wyboru dla transakcji
    setAccounts();
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu AccountManager, BankAccount i Ui
 */
TransactionWindow::~TransactionWindow()
{
    delete client_;
    delete accountManager_;
    delete account_;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku sendButton realizuje wysłanie transakcji pomiędzy kontami
 */
void TransactionWindow::on_sendButton_clicked()
{

    //Pobranie danych z pól interfejsu użytkownika
    std::string title = ui->titleInput->text().toStdString();
    double amount = ui->amountInput->text().toDouble();
    std::string reciver = ui->reciverInput->text().toStdString();
    std::string reciver_account = ui->reciverAccNumberInput->text().toStdString();
    std::string sender_account = ui->comboBox->currentText().toStdString();

    bool ok;

    QString toVerifyPIN = QInputDialog::getText(this, "Zatwierdź przelew", "Podaj kod PIN:", QLineEdit::Normal, "", &ok);

    if(ok && toVerifyPIN == QString::number(client_->getPIN())){

        //Wywołanie metody sendTransaction() w celu wykonania transakcji
        accountManager_->sendTransaction(reciver_account, reciver, sender_account, amount, title);

        //Wyczyszczenie pól interfejsu użytkownika
        ui->titleInput->clear();
        ui->amountInput->clear();
        ui->reciverInput->clear();
        ui->reciverAccNumberInput->clear();

    }else {

        QMessageBox::critical(this, "Błędny kod PIN", "Wprowadzony nieprawidłowy kod PIN");

    }
}

/*
 * Slot, który po wciśnięciu przycisku gobackButton realizuje zamknięcie okna statystyk
 */
void TransactionWindow::on_gobackButton_clicked()
{
    //Ukrycie bieżącego okna wysyłania transakcji
    hide();
}

/*
 * Funkcja która ustawia dostępne konta do wyboru w SelectionBox
 */
void TransactionWindow::setAccounts()
{
    ui->comboBox->addItem(QString::fromStdString(account_->getAccountNumber()));
}
