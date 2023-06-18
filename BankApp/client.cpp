
#include "client.h"
#include "accountmanager.h"

/*
 * Konstruktor
 */
Client::Client(const std::string& name, const std::string& surname, const std::string& email, const std::string& password, const QDate& dateOfBirth,
               const std::string& pesel, const std::string& phone_number, int pin) : name_(name), surname_(surname), email_(email), password_(password),
    date_of_birth_(dateOfBirth), pesel_(pesel), phone_number_(phone_number), pin_(pin)
{
    accManager = new AccountManager(this);
}

/*
 * Destruktor
 */
Client::~Client()
{
    delete accManager;
}

/*
 * Funkcja ustawiająca imię użytkownika
 */
void Client::setName(const std::string &name)
{
    name_ = name;
}

/*
 * Funkcja ustawiająca hasło użytkownika
 */
void Client::setPassword(const std::string &password)
{
    password_ = password;
}

/*
 * Funkcja ustawiająca nazwisko użytkownika
 */
void Client::setSurname(const std::string &surname)
{
    surname_ = surname;
}

/*
 * Funkcja ustawiająca datę urodzenia użytkownika
 */
void Client::setDateBirth(const QDate &date_of_birth)
{
    date_of_birth_ = date_of_birth;
}

/*
 * Funkcja ustawiająca email użytkownika
 */
void Client::setEmail(const std::string &email)
{
    email_ = email;
}

/*
 * Funkcja ustawiająca numer telefonu użytkownika
 */
void Client::setPhoneNumber(const std::string& phone_number)
{
    phone_number_ = phone_number;
}

/*
 * Funkcja ustawiająca pesel użytkownika
 */
void Client::setPesel(const std::string& pesel)
{
    pesel_ = pesel;
}

/*
 *  Funkcja ustawiająca menadżera kont
 */
void Client::setAccountManager(AccountManager *accountManager)
{
    this->accManager = accountManager;
}

/*
 * Funkcja ustawiająca kod PIN klienta
 */
void Client::setPIN(int pin)
{
    pin_ = pin;
}

/*
 * Funkcja zwracająca imię użytkownika
 */
std::string Client::getName() const
{
    return name_;
}

/*
 * Funkcja zwracająca hasło użytkownika
 */
std::string Client::getPassword() const
{
    return password_;
}

/*
 * Funkcja zwracająca nazwisko użytkownika
 */
std::string Client::getSurname() const
{
    return surname_;
}

/*
 * Funkcja zwracająca email użytkownika
 */
std::string Client::getEmail() const
{
    return email_;
}

/*
 * Funkcja zwracająca numer użytkownika
 */
std::string Client::getPhoneNumber() const
{
    return phone_number_;
}

/*
 * Funkcja zwracająca pesel użytkownika
 */
std::string Client::getPesel() const
{
    return pesel_;
}

/*
 * Funkcja zwracająca datę urodzenia użytkownika
 */
QDate Client::getDateBirth() const
{
    return date_of_birth_;
}

/*
 * Funkcja zwracająca menadżera kont
 */
AccountManager* Client::getAccountManager() const
{
    return this->accManager;
}

/*
 * Funkcja zwracająca imię i nazwisko użytkownika
 */
std::string Client::getFullname() const
{
    std::string fullname = getName() + " " + getSurname();

    return fullname;
}

/*
 * Funkcja zwracająca kod PIN klienta
 */
int Client::getPIN() const
{
    return pin_;
}

/*
 * Funkcja sprawdzająca poprawność wprowadzonego kodu PIN przez klienta
 */
bool Client::verifyPIN(int code)
{
    //Sprawdzenie czy podany kod jest równy temu przypisanemu do klienta
    if(pin_ == code)
    {
        //Zwrócenie wartości true
        return true;
    }

    //Zwrócenie wartości false w przypadku niepowodzenie
    return false;
}
