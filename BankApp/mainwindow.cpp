#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "registration.h"
#include "accountswindow.h"
#include "transactionwindow.h"
#include "creditcalculatorwindow.h"
#include "statisticswindow.h"
#include "mydatawindow.h"
#include "newaccountwindow.h"
#include "witdrawalwindow.h"

/*
 * Konstruktor
 */
MainWindow::MainWindow(QWidget *parent, Client *client, ClientManager *clientManager) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Inicjalizacja interfejsu użytkownika dla okna głównego menu
    ui->setupUi(this);

    //Przypisanie wskaźnika na obiekt client do pola client_
    client_ = client;

    //Przypisanie wskaźnika na obiekt clientManager do pola clientManager_
    clientManager_ = clientManager;
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu Client, AccuntsWindow, MyDataWindow, CalculatorWindow, StatsWindow, NewAccountWindow, WitdrawalWindow i Ui
 */
MainWindow::~MainWindow()
{
    delete client_;
    delete accountWindow;
    delete mydataWindow;
    delete calculatorWindow;
    delete statsWindow;
    delete newAccountWindow;
    delete withdrawalWindow;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku myAccountsButton powoduje otwarcie okna wyświetlającego konta klienta
 */
void MainWindow::on_myAccountsButton_clicked()
{
    //Utworzenie nowego obiektu AccountsWindow, przekazując wskaźnik na obiekt rodzica i wskaźnik na obiekt klienta
    accountWindow = new AccountsWindow(this, client_);

    //Wyświetlenie okna kont bankowych
    accountWindow->show();

}

/*
 * Slot, który po wciśnięciu przycisku myDataButton powoduje otwarcie okna wyświetlającego dane klienta
 */
void MainWindow::on_myDataButton_clicked()
{
    //Utworzenie nowego obiektu MyDataWindow, przekazując wskaźnik na obiekt rodzica i wskaźnik na obiekt klienta
    mydataWindow = new MyDataWindow(this, client_);

    //Wyświetlenie okna danych klienta
    mydataWindow->show();

}

/*
 * Slot, który po wciśnięciu przycisku myStatsButton powoduje otwarcie okna wyświetlającego statystki operacyjne klienta
 */
void MainWindow::on_myStatsButton_clicked()
{
    //Utworzenie nowego obiektu StatisticsWindow, przekazując wskaźnik na obiekt rodzica i wskaźnik na obiekt menadżera kont klienta
    statsWindow = new StatisticsWindow(this, client_->getAccountManager());

    //Wyświetlenie okna statystki operacyjne klienta
    statsWindow->show();

}

/*
 * Slot, który po wciśnięciu przycisku creditCalculatorButton powoduje otwarcie okna wyświetlającego kalkulator kredytu
 */
void MainWindow::on_creditCalculatorButton_clicked()
{
    //Utworzenie nowego obiektu creditCalculatorWindow, przekazując wskaźnik na obiekt rodzica i wskaźnik na obiekt klienta
    calculatorWindow = new creditCalculatorWindow(this, client_);

    //Wyświetlenie okna kalkulatora kredytu
    calculatorWindow->show();

}

/*
 * Slot, który po wciśnięciu przycisku logoutButton powoduje wylogowanie się klienta z systemu bankowego
 */
void MainWindow::on_logoutButton_clicked()
{

    //Utworzenie i przypisanie do obiektu accManager menadżera kont klienta
    AccountManager* accManager = client_->getAccountManager();

    //Zapisanie ewentualnych zmian w kontach do pliku tekstowego
    accManager->writeAccounts("C:\\Users\\Bartek\\Desktop\\BankApp\\accounts.txt");

    //Zamknięcie programu
    exit(0);
}

/*
 * Slot, który po wciśnięciu przycisku newAccountButton powoduje otwarcie okna, w którym klient może utworzyć nowe konto oszczędnościowe
 */
void MainWindow::on_newAccountButton_clicked()
{
    //Utworzenie nowego obiektu NewAccountWindow, przekazując wskaźnik na obiekt rodzica i wskaźnik na obiekt klienta
    newAccountWindow = new NewAccountWindow(this, client_);

    //Wyświetlenie okna zakładania nowego konta oszczędnościowego
    newAccountWindow->show();
}

/*
 * Slot, który po wciśnięciu przycisku witdrawalButton powoduje otwarcie okna do wypłacania środków z konta
 */
void MainWindow::on_witdrawalButton_clicked()
{
    //Utworzenie nowego obiektu WitdrawalWindow, przekazując wskaźnik na obiekt rodzica i wskaźnik na obiekt klienta
    withdrawalWindow = new WitdrawalWindow(this, client_);

    //Wyświetlenie okna do wypłacania środków z konta
    withdrawalWindow->show();
}


