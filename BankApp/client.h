
#ifndef CLIENT_H
#define CLIENT_H


#include <string>
#include <QDate>

class AccountManager;

class Client
{
private:
    //Pole przechowujące imię klienta
    std::string name_;
    //Pole przechowujące nazwisko klienta
    std::string surname_;
    //Pole przechowujące email klienta
    std::string email_;
    //Pole przechowujące hasło klienta
    std::string password_;
    //Pole przechowujące datę urodzenia klienta
    QDate date_of_birth_;
    //Pole przechowujące pesel klienta
    std::string pesel_;
    //Pole przechowujące numer telefonu klienta
    std::string phone_number_;
    //Pole przechowujące pin klienta
    int pin_;
    //Wskaźnik na obiekt AccountManager, który służy do zarządzania kontami
    AccountManager* accManager;

public:
    //Konstruktor
    //@param name przechowuje imię klienta
    //@param surname przechowuje nazwisko klienta
    //@param email przechowuje email klienta
    //@param password przechowuje hasło klienta
    //@param dateOfBirth przechowuje datę urodzenia klienta
    //@param pesel przechowuje pesel klienta
    //@param phone_number przechowuje numer telefonu klienta
    //@param pin przechowuje numer pin klienta
    Client(const std::string& name, const std::string& surname, const std::string& email, const std::string& password, const QDate& dateOfBirth,
           const std::string& pesel, const std::string& phone_number, int pin);
    //Destruktor
    ~Client();
    //Funkcja ustawiająca pole name_
    //@param name
    void setName(const std::string& name);
    //Funkcja ustawiająca pole password_
    //@param password
    void setPassword(const std::string& password);
    //Funkcja ustawiająca pole surname_
    //@param surname
    void setSurname(const std::string& surname);
    //Funkcja ustawiająca pole date_of_birth_
    //@param date_of_birth
    void setDateBirth(const QDate& date_of_birth);
    //Funkcja ustawiająca pole email_
    //@param email
    void setEmail(const std::string& email);
    //Funkcja ustawiająca pole pesel_
    //@param pesel
    void setPesel(const std::string& pesel);
    //Funkcja ustawiająca pole phone_number_
    //@param phone_number
    void setPhoneNumber(const std::string& phone_number);
    //Funkcja ustawiająca pole accManager
    //@param accountManager
    void setAccountManager(AccountManager* accountManager);
    //Funkcja ustawiająca pole pin_
    //@param pin
    void setPIN(int pin);
    //Funkcja zwracająca wartość pola name_
    std::string getName() const;
    //Funkcja zwracająca wartość pola password_
    std::string getPassword() const;
    //Funkcja zwracająca wartość pola surname_
    std::string getSurname() const;
    //Funkcja zwracająca wartość pola date_of_birth_
    QDate getDateBirth() const;
    //Funkcja zwracająca wartość pola email_
    std::string getEmail() const;
    AccountManager* getAccountManager() const;
    //Funkcja zwracająca wartość pola pesel_
    std::string getPesel() const;
    //Funkcja zwracająca wartość pola phone_number_
    std::string getPhoneNumber() const;
    //Funkcja zwracająca imię i nazwisko użytkownika
    std::string getFullname() const;
    //Funkcja zwracająca wartość pola pin_
    int getPIN() const;
    //Funkcja weryfikująca poprawność wprowadzonego pinu przez użytkownika
    //@param code kod pin podany przez użytkownika
    bool verifyPIN(int code);
};

#endif // CLIENT_H
