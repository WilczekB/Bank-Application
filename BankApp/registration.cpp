#include "registration.h"
#include "ui_registration.h"
#include "login.h"
#include <QInputDialog>

/*
 * Konstruktor
 */
Registration::Registration(QWidget *parent, Bank* bank) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    //Inicjalizacja interfejsu użytkownika dla okna rejestracji
    ui->setupUi(this);

    //Przypisanie wskaźnika na obiekt banku do zmiennej bank_
    bank_ = bank;

    //Przypisanie menadżera klientów banku do zmiennej clientManager_
    clientManager_ = bank->getClientManager();

    //Ustawienie maskowania pola do wprowadzania hasła
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez utworzone obiekty
 */
Registration::~Registration()
{
    delete clientManager_;
    delete loginWindow;
    delete bank_;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku registerButton realizuje proces rejestrowania się użytkownika
 * do systemu bankowego
 */
void Registration::on_registerButton_clicked()
{
    //Pobranie wartości wprowadzonych przez użytkownika
    QDate date_of_birth = ui->dateOfBirthEdit->date();
    std::string name = ui->nameEdit->text().toStdString();
    std::string surname = ui->surnameEdit->text().toStdString();
    std::string password = ui->passwordLineEdit->text().toStdString();
    std::string email = ui->emailEdit->text().toStdString();
    std::string phoneNumber = ui->phoneNumberEdit->text().toStdString();
    std::string pesel = ui->peselLineEdit->text().toStdString();
    int pin = ui->pinEdit->text().toInt();

    //Utworzenie nowego obiektu klasy Client
    Client* client = new Client(name, surname, email, password, date_of_birth, pesel, phoneNumber, pin);

    //Dodanie nowego klienta do clientManager
    if(clientManager_->addClient(client))
    {
        //Dopisanie nowego użytkownika do pliku tekstowego
        clientManager_->writeClientsToFile("C:\\Users\\Bartek\\Desktop\\BankApp\\clients.txt");
        //Wyświetlenie informacji dialogowej o udanej rejestracji użytkownika
        QMessageBox::information(this, "Prawidłowa rejestracja", "Udało Ci się zarejestrować w naszym systemie bankowym!");
    }

    //Wyczyszczenie wprowadzonych danych z GUI
    ui->dateOfBirthEdit->clear();
    ui->nameEdit->clear();
    ui->surnameEdit->clear();
    ui->passwordLineEdit->clear();
    ui->emailEdit->clear();
    ui->phoneNumberEdit->clear();
    ui->peselLineEdit->clear();

}

/*
 * Slot, który po wciśnięciu przycisku quitButton realizuje proces powrotu do
 * okna logowania, gdzie użytkownik może się już zalogować do systemu bankowego
 */
void Registration::on_quitButton_clicked()
{
    //Utworzenie nowego obiektu okna logowania
    loginWindow = new Login(this, bank_);

    //Wyświetlenie okna logowania
    loginWindow->show();

    //Ukrycie bieżącego okna rejestracji
    hide();
}

