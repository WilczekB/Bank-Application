
#ifndef BANK_H
#define BANK_H

#include "clientmanager.h"


class Bank
{
private:
    //Wskaźnik na obiekt ClientManager, który zarządza klientami
    ClientManager* clientManager;
public:
    //Konstruktor
    Bank();
    //Destruktor
    ~Bank();
    //Funkcja zwracająca wskaźnik na obiekt ClientManager
    ClientManager* getClientManager() const;
    //Funkcja logowania
    //
    //Funkcja realizuje proces logowania się użytkownika do systemu bankowego
    //@param password_ pole przechowujące hasło użytkownika
    //@param pesel_ pole przechowujące pesel użytkownika
    void login(std::string password_, std::string pesel_);
    //Funkcja wylogowania
    //
    //Funkcja realizuje proces wylogowania się użytkownika z systemu bankowego
    void logout();
    //Funkcja rejestracji
    //
    //Funkcja realizuje proces rejestracji nowego użytkownika do systemu bankowego
    void registration();
};

#endif // BANK_H
