#include "login.h"
#include "mainwindow.h"
#include "registration.h"
#include "ui_login.h"

/*
 * Konstruktor
 */
Login::Login(QWidget *parent, Bank* bank) :
    QDialog(parent),
    ui(new Ui::Login)
{
    //Inicjalizacja interfejsu użytkownika dla okna logowania
    ui->setupUi(this);
    //Przypisanie wskaźnika na obiekt bank do zmiennej bank_
    bank_ = bank;

    //Przypisanie menadżera klientów banku do zmiennej clientManager_
    clientManager_ = bank->getClientManager();

    //Ustawienie maskowania pola do wprowadzania hasła
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu Bank, MainWindow, RegistrationWindow, ClientManager i Ui
 */
Login::~Login()
{
    delete bank_;
    delete mainWindow;
    delete registrationWindow;
    delete clientManager_;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku loginButton realizuje proces logowania się użytkownika
 * do głównego menu systemu bankowego
 */
void Login::on_loginButton_clicked()
{

    //Pobranie wartości wprowadzonych przez użytkownika
    std::string password = ui->passwordLineEdit->text().toStdString();
    std::string pesel = ui->peselLineEdit->text().toStdString();

    //Weryfikacja logowanie
    if(clientManager_->verifyClient(pesel, password))
    {
        //W przypadku zwrócenia wartości true przez funkcję verifyClient()
        //Utworzenie obiektu głównego menu i wyświetlenie go
        //Zamknięcie okna logowania
        mainWindow = new MainWindow(this, clientManager_->findClient(pesel), clientManager_);
        mainWindow->show();
        hide();
    }else{
        //W przypadku zwrócenia wartości false przez funkcję verifyClient()
        //Pojawienie się okna dialogowego inforumującego użytkownika o błędnym logowaniu
        QMessageBox::critical(this, "Błąd logowania", "Nieudana próba logowania. Spróbuj ponowanie");
    }
}

/*
 * Slot, który po wciśnięciu przycisku registerButton realizuje proces otworzenia się
 * okna rejestracji, gdzie nowy użytkownik może się zarejstrować do systemu bankowego
 */
void Login::on_registerButton_clicked()
{
    //Utworzenie nowego obiektu okna rejestracji
    registrationWindow = new Registration(this, bank_);

    //Wyświetlenie okna rejestracji
    registrationWindow->show();

    //Ukrycie bieżącego okna logowania
    hide();

}

void Login::on_exitButton_clicked()
{
    exit(0);
}

