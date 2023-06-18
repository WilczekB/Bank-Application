#include "newaccountwindow.h"
#include "ui_newaccountwindow.h"
#include "savingsaccount.h"
#include <QInputDialog>

/*
 * Konstruktor
 */
NewAccountWindow::NewAccountWindow(QWidget *parent, Client *client) :
    QDialog(parent),
    ui(new Ui::NewAccountWindow)
{
    //Inicjalizacja interfejsu użytkownika dla okna zakładania nowego konta oszczędnościowego
    ui->setupUi(this);

    //Przypisanie wskaźnika na obiekt Client do pola client_
    client_ = client;

    //Przypisanie wskaźnika na obiekt AccountManager clienta do pola accountManager
    accountManager = client->getAccountManager();
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu AccountManager, Client i Ui
 */
NewAccountWindow::~NewAccountWindow()
{
    delete accountManager;
    delete client_;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku createAccountButton powoduje utworzenie
 * nowego konta oczędnościowego i dodanie go do menadżera kont klienta
 */
void NewAccountWindow::on_createAccountButton_clicked()
{
    //Pobranie wartości od użytkownika systemu
    double interest_rate = ui->interestSpinBox->value();
    int withdrawal_limit = ui->withdrawalSpinBox->value();

    bool ok;

    QString toVerifyPIN = QInputDialog::getText(this, "Zatwierdź przelew", "Podaj kod PIN:", QLineEdit::Normal, "", &ok);

    if(ok && toVerifyPIN == QString::number(client_->getPIN()))
    {

        //Utworzenie nowego obiektu konta oszczędnościowego
        SavingsAccount *account = new SavingsAccount("", 0.0, interest_rate, withdrawal_limit, client_->getPesel());

        //Wygenerowanie unikalnego numeru konta
        account->setAccountNumber();

        //Dodanie konta do vectora przechowującego wszystkie konta bankowe
        accountManager->addAccount(account);

        //Wyświetlenie komunikatu o udanym utworzeniu nowego konta
        QMessageBox::information(this,"Udana operacja", "Udało się utworzyć nowe konto oszczędnościowe.");

    }else {

        QMessageBox::critical(this, "Błędny kod PIN", "Wprowadzony nieprawidłowy kod PIN");

    }

    //Wyczyszczenie danych wpisanych przez użytkownika
    ui->interestSpinBox->clear();
    ui->withdrawalSpinBox->clear();

}

/*
 * Slot, który po wciśnięciu przycisku exitButton powoduje zamknięcie
 * interfejsu okna zakładania nowego konta oszczędnościowego
 */
void NewAccountWindow::on_exitButton_clicked()
{
    //Ukrycie bieżącego okna zakładania nowego konta oszczędnościowego
    hide();
}

