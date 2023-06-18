#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bank.h"
#include "accountswindow.h"
#include "mydatawindow.h"
#include "statisticswindow.h"
#include "creditcalculatorwindow.h"
#include "newaccountwindow.h"
#include "witdrawalwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param client wskaźnik do obiekt klasy Client
    //@param clientManager wskaźnik na obiekt klasy ClientManager
    explicit MainWindow(QWidget *parent = nullptr, Client *client = nullptr, ClientManager *clientManager = nullptr);
    //Destruktor
    ~MainWindow();

private slots:
    //Slot realizujący przejście do interfejsu accountswindow
    void on_myAccountsButton_clicked();

    //Slot realizujący przejście do interfejsu mydatawindow
    void on_myDataButton_clicked();

    //Slot realizujący przejście do interfejsu statisticswindow
    void on_myStatsButton_clicked();

    //Slot realizujący przejście do interfejsu creditcalculatorwindow
    void on_creditCalculatorButton_clicked();

    //Slot realizujący wyjście z systemu
    void on_logoutButton_clicked();

    //Slot realizujący przejście do interfejsu newaccountwindow
    void on_newAccountButton_clicked();

    //Slot realizujący przejście do interfejsu witdrawalwindow
    void on_witdrawalButton_clicked();

private:
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::MainWindow *ui;
    //Wskaźnik na obiekt klasy Client
    Client *client_;
    //Wskaźnik na obiekt klasy ClientManager
    ClientManager *clientManager_;
    //Wskaźnik na obiekt klasy AccountsWindow
    AccountsWindow *accountWindow;
    //Wskaźnik na obiekt klasy StatisticsWindow
    StatisticsWindow *statsWindow;
    //Wskaźnik na obiekt klasy MyDataWindow
    MyDataWindow *mydataWindow;
    //Wskaźnik na obiekt klasy creditCalculatorWindow
    creditCalculatorWindow *calculatorWindow;
    //Wskaźnik na obiekt klasy NewAccountWindow
    NewAccountWindow *newAccountWindow;
    //Wskaźnik na obiekt klasy WitdrawalWindow
    WitdrawalWindow *withdrawalWindow;
};

#endif // MAINWINDOW_H
