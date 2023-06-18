
#include "clientmanager.h"

/*
 * Konstruktor
 */
ClientManager::ClientManager()
{
    //Wywołanie funkcji w celu odczytu klientów z pliku
    this->readClientsFromFile();
}

/*
 * Destruktor
 */
ClientManager::~ClientManager()
{
    //Zwolnienie pamięci zajmowanej przez obiekty klientów
    for(auto client : clients)
    {
        delete client;
    }

    //Zwolnienie pamięci zajmowanej przez obiekt emailSender
    delete emailSender;
}

/*
 * Funkcja aktualizująca plik tekstowy o zmiany danych personalnych wybranego klienta
 */
void ClientManager::updateClient(Client *clientUpdated)
{

    //Otwarcie pliku wejściowego i pliku tymczasowego wyjściowego do zapisu zaktualizowanych danych
    std::ifstream inputFile("C:\\Users\\Bartek\\Desktop\\BankApp\\clients.txt");
    std::ofstream outputFile("tempFile.txt");

    //Sprawdzenie czy pliki otworzyły się prawidłowo
    if(inputFile.is_open() && outputFile.is_open())
    {
        std::string line;

        //Przejście przez plik wejściowy linia po linii
        while(std::getline(inputFile, line))
        {
            //Sprawdzenie czy linia zawiera numer pesel klienta do aktualizacji
            if(line.find(clientUpdated->getPesel()) != std::string::npos)
            {
                //Zapisanie zaktualizowanych danych do pliku wyjściowego
                outputFile << clientUpdated ->getName() << " " <<
                    clientUpdated->getSurname() << " " <<
                    clientUpdated->getDateBirth().toString(Qt::ISODate).toStdString() << " " <<
                    clientUpdated->getEmail() << " " <<
                    clientUpdated->getPesel() << " " <<
                    clientUpdated->getPhoneNumber() << " " <<
                    clientUpdated->getPassword() << "\n";
            } else {

                //Przepisanie pozostałych linii do pliku wyjściowego
                outputFile << line << "\n";
            }
        }

        //Zamknięcie pliku wejściowego i wyjściowego
        inputFile.close();
        outputFile.close();

        //Usunięcie pierwotnego pliku i sprawdzenie czy operacja się powiodła
        if(std::remove("C:\\Users\\Bartek\\Desktop\\BankApp\\clients.txt") != 0)
        {
            std::cerr << "Nie udalo sie usunac pliku" << '\n';
        }

        //Zmiana nazwy pliku tymczasowego na oryginalną nazwę pliku
        std::rename("tempFile.txt", "C:\\Users\\Bartek\\Desktop\\BankApp\\clients.txt");

    } else {

        //Wyrzucenie informacji o nieudanym otwarciu pliku
        std::cerr << "Nie udalo sie otworzyc pliku" << '\n';
    }
}

/*
 * Funkcja wczytująca klientów i ich dane z pliku tekstowego
 */
void ClientManager::readClientsFromFile()
{
    //Otwarcie pliku do odczytu
    std::ifstream inputFile("C:\\Users\\Bartek\\Desktop\\BankApp\\clients.txt");
    //Sprawdzenie czy plik został otwarty prawidłowo
    if(!inputFile.is_open())
    {
        //Wyrzucenie wyjątku w przypadku braku możliwości otwarcia pliku
        throw std::runtime_error("Nie udalo sie otworzyc pliku");

    }

    std::string line;
    //Pętla while() przechodząca linia po linii w pliku
    while(std::getline(inputFile, line))
    {
        //Inicjalizacja strumienia istringstream z aktualnej odczytanej linii
        std::istringstream iss(line);

        //Inicjalizacja zmiennych do parametrów klienta
        std::string pesel, phoneNumber;
        std::string name, surname, email, password;
        std::string dateOfBirth_;
        int pin;

        //Wczytanie danych z linii do odpowiednich zmiennych
        if(!(iss >> name >> surname >> dateOfBirth_ >> email >> pesel >> phoneNumber >> password >> pin))
        {
            //Wyrzucenie wyjątku w przypadku wystąpienia błędu podczas odczytu danych
            throw std::runtime_error("Blad podczas odczytu pliku");
        }

        //Konwertowanie daty urodzenia z formatu string na QDate
        QDate dateOfBirth = QDate::fromString(QString::fromStdString(dateOfBirth_), "yyyy-MM-dd");

        //Utworzenie nowego obiektu Client na podstawie wczytanych danych
        Client* client = new Client(name, surname, email, password, dateOfBirth, pesel, phoneNumber, pin);

        //Dodanie nowego klienta do vectora clients
        this->clients.push_back(client);
    }

    //Zamknięcie pliku
    inputFile.close();
}

/*
 * Funkcja zapisująca klientów i ich dane do pliku tekstowego
 */
void ClientManager::writeClientsToFile(std::string file_name)
{
    //Otwarcie pliku do zapisu
    std::ofstream outputFile(file_name);

    //Sprawdzenie czy plik został otwarty prawidłowo
    if(!outputFile.is_open())
    {
        //Wyrzucenie wyjątku w przypadku braku możliwości otwarcia pliku
        throw std::runtime_error("Nie udalo sie otworzyc pliku");
    }

    //Pętla for() iterująca po każdym kliencie w vectorze clients
    for(auto client : clients) {

        //Zapis danych klienta do pliku w odpowiednim formacie
        outputFile << client ->getName() << " " <<
            client->getSurname() << " " <<
            client->getDateBirth().toString(Qt::ISODate).toStdString() << " " <<
            client->getEmail() << " " <<
            client->getPesel() << " " <<
            client->getPhoneNumber() << " " <<
            client->getPassword() << " " <<
            client->getPIN() << "\n";

    }

    //Zamknięcie pliku
    outputFile.close();
}

/*
 * Funkcja weryfikująca klienta w systemie na podstawie podanego numer pesel i hasła
 */
bool ClientManager::verifyClient(const std::string& pesel, const std::string& password)
{
    //Pętla for() iterująca po każdym kliencie w vectorze clients
    for(auto client : clients)
    {
        //Warunek sprawdzający czy pesel i hasło klienta są zgodne z podanymi wartościami
        if(client->getPesel() == pesel && client->getPassword() == password)
        {
            //W przypadku pozytywnej weryfikacji klienta, zwracamy true
            return true;
        }
    }

    //W przypadku negatywnej weryfikacji klienta, zwracamy false
    return false;
}

/*
 * Funkcja dodająca klienta do vectora clients
 */
bool ClientManager::addClient(Client *client)
{
    //Dodanie obiektu client do vectora clients
    clients.push_back(client);

    //Warunek if() sprawdzający, czy udało się dodać obiekt do vectora
    if(std::find(clients.begin(), clients.end(), client) != clients.end())
    {
        //W przypadku powodzenia zwraca wartość true
        return true;
    }

    //W innym przypadku zwraca wartość false
    return false;
}

/*
 * Funkcja znajdująca klienta na podsawie peselu
 */
Client* ClientManager::findClient(std::string pesel) const
{
    //Funkcja for() iterująca po każdym obiekcie w vectorze clients
    for(Client* client : clients)
    {
        //Warunek sprawdzający, czy pesel klienta zgadza się z poszukiwanym
        if(client->getPesel() == pesel)
        {
            //Zwracany obiekt client
            return client;
        }
    }
    //W przypadku nie znaleziena danego klienta, zwracana jest domyślnie wartość nullptr
    return nullptr;
}


