
#include "bank.h"

/*
 * Konstruktor
 */
Bank::Bank()
{
    this->clientManager = new ClientManager();
}

/*
 * Destruktor
 * Zwalnia pamięć dla wskaźnika do obiektu clientManager
 */
Bank::~Bank()
{
    delete clientManager;
}

/*
 * Funkcja umożliwiająca użytkownikowi zalogowanie się
 */
void Bank::login(std::string password_, std::string pesel_)
{

}

/*
 * Funkcja umożliwiając użytkownikowi wylogowanie się
 */
void Bank::logout()
{

}

/*
 * Funkcja umożliwiająca użytkownikowi zarejestrowanie się
 */
void Bank::registration()
{

}

/*
 * Funkcja zwracająca menadżera klientów banku
 */
ClientManager* Bank::getClientManager() const
{
    return clientManager;
}
