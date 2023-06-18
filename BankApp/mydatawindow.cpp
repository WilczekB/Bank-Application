#include "mydatawindow.h"
#include "ui_mydatawindow.h"

/*
 * Konstruktor
 */
MyDataWindow::MyDataWindow(QWidget *parent, Client* client, ClientManager *clientManager) :
    QDialog(parent),
    ui(new Ui::MyDataWindow)
{
    //Inicjalizacja interfejsu użytkownika dla okna danych klienta
    ui->setupUi(this);

    //Przypisanie wskaźnika na obiekt client do pola client_
    client_ = client;

    //Przypisanie wskaźnika na obiekt clientManager do pola clientManager_
    clientManager_ = clientManager;

    //Wywołanie metody wyświetlającej dane klienta
    setMyData();
}

/*
 * Destruktor
 * Zwolnienie pamięci zajmowanej przez obiekty typu Client i Ui
 */
MyDataWindow::~MyDataWindow()
{
    delete clientManager_;
    delete client_;
    delete ui;
}

/*
 * Slot, który po wciśnięciu przycisku changeButton powoduje aktaulizację danych klienta
 */
void MyDataWindow::on_changeButton_clicked()
{

    //Pobranie nowych wartości z QLineEdit
    QDate date_of_birth = QDate::fromString(ui->dateOfBirthOutput->text(), Qt::ISODate);
    std::string name = ui->nameOutput->text().toStdString();
    std::string surname = ui->surnameOutput->text().toStdString();
    std::string password = ui->passwordOutput->text().toStdString();
    std::string email = ui->emailOutput->text().toStdString();
    std::string phoneNumber = ui->phoneNumberOutput->text().toStdString();
    std::string pesel = ui->peselOutput->text().toStdString();

    //Ustawienie nowych wartości w obiekcie client
    client_->setName(name);
    client_->setSurname(surname);
    client_->setDateBirth(date_of_birth);
    client_->setPassword(password);
    client_->setEmail(email);
    client_->setPhoneNumber(phoneNumber);
    client_->setPesel(pesel);

    //Zapisanie zmian do pliku tekstowego
    clientManager_->updateClient(client_);

    //Wyświetlenie komunikatu o zaktualizowaniu danych użytkownika
    QMessageBox::information(this, "Zmiana danych personalnych", "Dokonano zmiany treści, dotyczących danych personalnych.");
}

/*
 * Slot, który po wciśnięciu przycisku exitButton powoduje zamknięcie okna danych klienta
 */
void MyDataWindow::on_exitButton_clicked()
{
    //Ukrycie okna danych klienta
    hide();
}

/*
 * Funkcja ustawiająca dane klienta
 */
void MyDataWindow::setMyData()
{

    //Ustawienie wybranych pól edycyjnych tylko do odczytu
    ui->peselOutput->setReadOnly(true);
    ui->dateOfBirthOutput->setReadOnly(true);
    ui->nameOutput->setReadOnly(true);
    ui->surnameOutput->setReadOnly(true);

    //Utworzenie zmiennych do przechowania danych o kliencie i odpowiednie konwersja danych
    QString date_of_birth = client_->getDateBirth().toString("yyyy-MM-dd");
    QString name = QString::fromStdString(client_->getName());
    QString surname = QString::fromStdString(client_->getSurname());
    QString password = QString::fromStdString(client_->getPassword());
    QString email = QString::fromStdString(client_->getEmail());
    QString phoneNumber = QString::fromStdString(client_->getPhoneNumber());
    QString pesel = QString::fromStdString(client_->getPesel());

    //Ustawienie odpowiednich wartości do wyświetlenie w GUI
    ui->nameOutput->setText(name);
    ui->surnameOutput->setText(surname);
    ui->emailOutput->setText(email);
    ui->passwordOutput->setText(password);
    ui->dateOfBirthOutput->setText(date_of_birth);
    ui->phoneNumberOutput->setText(phoneNumber);
    ui->peselOutput->setText(pesel);
}
