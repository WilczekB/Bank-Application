#include "statisticswindow.h"
#include "mainwindow.h"
#include "ui_statisticswindow.h"

/*
 * Konstruktor
 */
StatisticsWindow::StatisticsWindow(QWidget *parent, AccountManager *accountManager) :
    QDialog(parent),
    ui(new Ui::StatisticsWindow)
{
    //Inicjalizacja interfejsu użytkownika dla okna statystyk
    ui->setupUi(this);

    //Przypisanie wskaźnika do menadżera kont
    accountManager_ = accountManager;

    //Wywołanie funkcji do wyświetlenia statystyk konta
    showStats();
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu AccountManager i Ui
 */
StatisticsWindow::~StatisticsWindow()
{
    delete accountManager_;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku gobackButton realizuje zamknięcie okna statystyk
 */
void StatisticsWindow::on_gobackButton_clicked()
{
    //Ukrycie bieżącego okna statystyk
    hide();
}

/*
 * Funkcja wyświetlająca statystyki odnośnie konta
 */
void StatisticsWindow::showStats()
{
    //Ustawienie tekstu w polach tekstowych na podstawie wyliczonych statystyk
    ui->expenseLineEdit->setText(QString::number(accountManager_->calcualteExpanse()));
    ui->incomeLineEdit->setText(QString::number(accountManager_->calculateProfit()));
    ui->balanceLineEdit->setText(QString::number(accountManager_->calculateBalance()));
}
