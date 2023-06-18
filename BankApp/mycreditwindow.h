#ifndef MYCREDITWINDOW_H
#define MYCREDITWINDOW_H

#include <QDialog>
#include "client.h"
#include "bankaccount.h"
#include "accountmanager.h"
#include "credit.h"
#include "creditschedule.h"

namespace Ui {
class MyCreditWindow;
}

class MyCreditWindow : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param client wskaźnik do obiektu klasy Client
    explicit MyCreditWindow(QWidget *parent = nullptr, Client *client = nullptr);
    //Destruktor
    ~MyCreditWindow();

private slots:
    //Slot realizujący spłatę raty miesięcznej i wyświetlenie następnej
    void on_updateButton_clicked();

    //Slot realizujący wyjście z interfejsu MyCreditWindow
    void on_exitButton_clicked();

    //Slot realizujący przekazanie wybranego w QComboBox numeru konta kredytowego
    void on_creditNumberBox_currentTextChanged(const QString &arg1);

private:
    //Funkcja ustawiająca dane o harmonogramie spłaty kredytu
    //@param accNumber przechowuje wybrany  numer konta kredytowego
    void setData(const std::string accNumber);
    //Funckja ustawiająca numery kont kredytowych w QComboBox
    void setComboBox();
    //Funkcja ustawiająca pola tekstowe tylko do odczytu
    void setToReadOnly();
    //Funkcja ustawiająca pierwotne ogólne dane dotyczące kredytu
    void setInitialText();
    //Funkcja aktualizująca raty kapitałowe
    //@param capital przechowuje kwotę raty kapitałowej
    void updateCapitalPayment(double capital);
    //Funkcja aktualizująca raty odsetkowe
    //@param interest przechowuje kwotę raty odsetkowej
    void updateInterestPayment(double interest);
    //Funkcja aktualizująca datę kolejnej raty kredytowej
    //@param date przechowuje kolejną datę
    void updateDate(const std::string date);
    //Funkcja aktualizująca kolejne saldo zadłużenia
    //@param balance przechowuje kolejne saldo zadłużenia
    void updateBalance(double balance);
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::MyCreditWindow *ui;
    //Wskaźnik na obiekt klasy Client
    Client *client_;
    //Wskaźnik na obiekt klasy AccountManager
    AccountManager *accManager;
    //Wskaźnik na obiekt klasy CreditSchdule
    CreditSchedule *creditSchedule;
};

#endif // MYCREDITWINDOW_H
