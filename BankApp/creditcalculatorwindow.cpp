#include "creditcalculatorwindow.h"
#include "ui_creditcalculatorwindow.h"
#include <QInputDialog>

/*
 * Konstruktor
 */
creditCalculatorWindow::creditCalculatorWindow(QWidget *parent, Client *client) :
    QDialog(parent),
    ui(new Ui::creditCalculatorWindow)
{
    //Inicjalizacja interfejsu użytkownika dla okna kalkulatora kredytu
    ui->setupUi(this);

    //Przypisanie wskaźnika na obiekt client do pola client_
    client_ = client;

    accManager = client->getAccountManager();

    //Ustawienie aktualnej daty
    ui->dateEdit->setDate(QDate::currentDate());
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu Calculator, Client i Ui
 */
creditCalculatorWindow::~creditCalculatorWindow()
{
    delete client_;
    delete ui;
}

/*
 * Funkcja czyszcząca pola do wpisywania danych
 */
void creditCalculatorWindow::clear()
{
    ui->dateEdit->setDate(QDate::currentDate());
    ui->commisionInput->clear();
    ui->financialPeriodInput->clear();
    ui->investmentValueInput->clear();
    ui->percentageInput->clear();
}

/*
 * Slot, który po wciśnięciu przycisku clearButton powoduje wyczyszczenie pól do wpisywania danych
 */
void creditCalculatorWindow::on_clearButton_clicked()
{
    //Wywołanie metody czyszczenia wszystkich pól
    clear();
}

/*
 * Slot, który po wciśnięciu przycisku generateScheduleButton powoduje utworzenie harmonogramu spłaty kredytu w pliku tekstowym
 */
void creditCalculatorWindow::on_generateScheduleButton_clicked()
{

    //Pobranie danych od użytkownika
    double comission = ui->commisionInput->text().toDouble();
    double percentage = ui->percentageInput->text().toDouble();
    double investment_value = ui->investmentValueInput->text().toDouble();
    int financial_period = ui->financialPeriodInput->text().toInt();
    QDate start_date = ui->dateEdit->date();

    //Utworzenie nowego obiektu typu Credit
    Credit* credit = new Credit("", investment_value, start_date, financial_period, investment_value, percentage, comission, client_->getPesel());

    //Wygenerowanie unikalnego numeru konta
    credit->setAccountNumber();
/*
    //Utworzenie nowego obiektu typu CreditCalculator
    CreditCalculator* calculator = dynamic_cast<CreditCalculator*>(credit->getCalculator());

    //Wyliczenie miesięscznych rat i utworzenie harmonogramu spłat
    calculator->calculate();
*/

    //Wyświetlenie okna dialogowego z prośbą o wprowadzenie kodu PIN
    bool ok;
    QString toVerifyPIN = QInputDialog::getText(this, "Zatwierdź przelew", "Podaj kod PIN:", QLineEdit::Normal, "", &ok);

    //Warunek sprawdzający poprawność wpisanego kodu PIN przez użytkownika
    if(ok && toVerifyPIN == QString::number(client_->getPIN())){

        //Utworzenie nowego obiektu typu CreditCalculator
        CreditCalculator *calculator = new CreditCalculator(credit);

        //Wyliczenie miesięscznych rat i utworzenie harmonogramu spłat
        calculator->calculate();

        //Dodanie nowego konta do menadżera kont
        accManager->addAccount(dynamic_cast<BankAccount*>(credit));

        //Wyświetlenie komunikatu o udanym zaciągnięciu kredytu
        QMessageBox::information(this, "Gratulacje", "Pomyślnie rozpatrzenie wniosku kredytowego");

        //Wywołanie metody czyszczenia wszystkich pól
        clear();

    }else {

        //W przypadku błędnego kodu PIN wyświetlenie komunikatu o błędzie
        QMessageBox::critical(this, "Błędny kod PIN", "Wprowadzony nieprawidłowy kod PIN");

    }

}

/*
 * Slot, który po wciśnięciu przycisku gobackButton powoduje ukrycie okna kalkulatora kredytu
 */
void creditCalculatorWindow::on_gobackButton_clicked()
{
    //Ukrycie okna kalkulatora kredytu
    hide();
}

