#ifndef ACCOUNTSWINDOW_H
#define ACCOUNTSWINDOW_H

#include <QDialog>
#include "accountmanager.h"
#include "transactionwindow.h"
#include "mycreditwindow.h"

namespace Ui {
class AccountsWindow;
}

class AccountsWindow : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param client wskaźnik do obiektu klasy Client
    explicit AccountsWindow(QWidget *parent = nullptr, Client *client = nullptr);
    //Destruktor
    ~AccountsWindow();

private slots:
    //Slot do wyświetlenia interfejsu transakcji
    //
    //Po wciśnięciu przycisku sendTransactionButton następuje przejście do interfejsu wysyłania transferów
    void on_sendTransactionButton_clicked();

    //Slot do wyjścia z interfejsu
    //
    //Po wciśnięciu przycisku goBackButton zamykany jest interfejs accountswindow
    void on_goBackButton_clicked();

    //Slot do wyświetlania danych wybranego konta
    //
    //Po wybraniu i kliknięciu na odpowiedni numer konta, następuje aktualizacja danych o koncie
    void on_accountsComboBox_currentTextChanged(const QString &arg1);

    //Slot do wyświetlenia interfejsu harmonogramu spłaty kredytu
    //
    //Po wciśnięciu przycisku myCreditButton następuje przejście do interfejsu harmonogramu spłat kredytu
    void on_myCreditButton_clicked();

private:
    //Funkcja do ustawiania QComboBox
    //
    //Funkcja wypełnia QComboBox wszystkimi numerami kont, jakie posiada użytkownik
    void setSelectionBox();
    //Funkcja do ustawiania informacji o transakcji
    //
    //Funkcja pobiera i wyświetla wszystkie transakcje jakich dokonał użytkownik
    //@param acc_number numer wybranego konta bankowego
    void setTransactionsData(const std::string acc_number);
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::AccountsWindow *ui;
    //Wskaźnik na obiekt AccountManager, który zarządza kontami
    AccountManager *accountManager_;
    //Wskaźnik na obiekt Client, który reprezentuje klienta
    Client *client_;
    //Wskaźnik na obiekt TransactionWindow, który jest odpowiedzialny za obsługę okna transackji
    TransactionWindow *transactionWindow;
    //Wskaźnik na obiekt MyCreditWindow, który jest odpowiedzialny za obsługę okna harmonogramu spłat kredytu
    MyCreditWindow *myCreditWindow;
};

#endif // ACCOUNTSWINDOW_H
