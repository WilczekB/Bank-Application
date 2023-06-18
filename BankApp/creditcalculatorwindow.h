#ifndef CREDITCALCULATORWINDOW_H
#define CREDITCALCULATORWINDOW_H

#include <QDialog>
#include "credit.h"
#include "creditcalculator.h"
#include "client.h"
#include "accountmanager.h"

namespace Ui {
class creditCalculatorWindow;
}

class creditCalculatorWindow : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param client wskaźnik do obiekut klasy Client
    explicit creditCalculatorWindow(QWidget *parent = nullptr, Client* client = nullptr);
    //Destruktor
    ~creditCalculatorWindow();

private slots:
    //Slot do wyczyszczenia pól tekstowych z danych
    void on_clearButton_clicked();

    //Slot do wygenerowania harmonogramu spłaty kredytu
    void on_generateScheduleButton_clicked();

    //Slot do wyjścia z interfejsu
    //
    //Po wciśnięciu przycisku goBackButton zamykany jest interfejs creditcalculatorwindow
    void on_gobackButton_clicked();

private:
    //Funkcja która czyści pola tekstowe z danych
    void clear();
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::creditCalculatorWindow *ui;
    //Wskaźnik na obiekt Client, który reprezentuje klienta
    Client *client_;
    //Wskaźnik na obiekt AccountManager, który zarządza kontami
    AccountManager *accManager;
};

#endif // CREDITCALCULATORWINDOW_H
