#ifndef WITDRAWALWINDOW_H
#define WITDRAWALWINDOW_H

#include <QDialog>
#include "client.h"
#include "accountmanager.h"
#include "bankaccount.h"
#include <QMessageBox>

namespace Ui {
class WitdrawalWindow;
}

class WitdrawalWindow : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param client wskaźnik na obiekt klasy Client
    explicit WitdrawalWindow(QWidget *parent = nullptr, Client *client = nullptr);
    //Destruktor
    ~WitdrawalWindow();

private slots:
    //Slot realizujący wypłatę środków z konta
    void on_withdrawButton_clicked();

    //Slot realizujący zamknięcie interfesju WitdrawalWindow
    void on_exitButton_clicked();

    //Slot realizujący wpłatę środków na konto
    void on_depositButton_clicked();

    void on_randAmountButton_clicked();

    void on_accountSelectionBox_currentTextChanged(const QString &arg1);

private:
    void setBalance(std::string acc_number);
    //Funkcja ustawiająca wybrane konto bankowe
    void setAccounts();
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::WitdrawalWindow *ui;
    //Wskaźnik na obiekt klasy Client
    Client *client_;
    //Wskaźnik na obiekt klasy AccountManager
    AccountManager *accountManager_;
};

#endif // WITDRAWALWINDOW_H
