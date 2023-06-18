
#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "emailsender.h"
#include "client.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <QString>
#include <iomanip>
#include <iostream>

class ClientManager
{
private:
    //Wektor wskaźników do obiektów klasy Client, który przechowuje wszystkich klientów w systemie
    std::vector<Client*> clients;
    //Wskaźnik na obiekt klasy EmailSender, który wysyła weryfikacyjny kod
    EmailSender* emailSender;
public:
    //Konstruktor
    ClientManager();
    //Destruktor
    ~ClientManager();
    //Funkcja zapisująca do pliku tekstowego zmienione dane użytkownika
    //@param clientUpdated wskaźnik na obiekt klasy Client
    void updateClient(Client *clientUpdated);
    //Funkcja weryfikujaca poprawność zalogowania się klienta do systemu
    //@param pesel przechowuje podany pesel użytkownika
    //@param password przechowuje podane hasło użytkownika
    bool verifyClient(const std::string& pesel, const std::string& password);
    //Funkcja wczytująca klientów z pliku tekstowego
    void readClientsFromFile();
    //Funkcja zapisująca klientów do pliku tekstowego
    void writeClientsToFile(std::string file_name);
    //Funkcja dodająca nowy obiekt klasy Client do wektora clients
    //@param client wskaźnik na obiekt klasy Client nowego klienta
    bool addClient(Client* client);
    //Funkcja znajdująca i zwracająca klienta
    //
    //Funkcja szuka w wektorze clients danego klienta po numerze pesel i zwraca wskaźnik na ten obiekt
    //@param pesel, numer pesel po którym jest szukany klient
    Client* findClient(std::string pesel) const;

};

#endif // CLIENTMANAGER_H
