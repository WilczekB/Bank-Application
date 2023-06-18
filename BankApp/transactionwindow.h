#ifndef TRANSACTIONWINDOW_H
#define TRANSACTIONWINDOW_H

#include <QDialog>
#include "accountmanager.h"
#include "client.h"
#include <QMessageBox>

namespace Ui {
class TransactionWindow;
}

class TransactionWindow : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param accountManager wskaźnik na obiekt klasy AccountManager
    //@param account wskaźnik na obiekt klasy BankAccount
    //@param client wskaźnik na obiekt klasy Client
    explicit TransactionWindow(QWidget *parent = nullptr, AccountManager *accountManager = nullptr, BankAccount *account = nullptr, Client *client = nullptr);
    //Destruktor
    ~TransactionWindow();

private slots:
    //Slot realizujący wysłanie transakcji
    void on_sendButton_clicked();

    //Slot realizujący zamknięcie interfesju TransactionWindow
    void on_gobackButton_clicked();

private:
    //Funkcja ustawiająca wybrane konto bankowe do transferu
    void setAccounts();
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::TransactionWindow *ui;
    //Wskaźnik na obiekt klasy AccountManager
    AccountManager* accountManager_;
    //Wskaźnik na obiekt klasy BankAccount
    BankAccount *account_;
    //Wskaźnik na obiekt klasy Client
    Client *client_;
};

#endif // TRANSACTIONWINDOW_H
