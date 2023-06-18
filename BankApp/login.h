#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
//#include "registration.h"
#include "mainwindow.h"
#include "bank.h"

class Registration;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param bank wskaźnik do obiekt klasy Bank
    explicit Login(QWidget *parent = nullptr, Bank* bank = nullptr);
    //Destruktor
    ~Login();

private slots:
    //Slot po którym następuje logowanie i przejście do menu głównego
    void on_loginButton_clicked();

    //Slot po który następuje przejście do interfejsu rejestracji nowego użytkownika
    void on_registerButton_clicked();

    //Slot do wyjścia z interfejsu
    //
    //Po wciśnięciu przycisku goBackButton zamykany jest interfejs accountswindow
    void on_exitButton_clicked();

private:
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::Login *ui;
    //Wskaźnik na obiekt klasy Registration
    Registration *registrationWindow;
    //Wskaźnik na obiekt klasy MainWindow
    MainWindow *mainWindow;
    //Wskaźnik na obiekt klasy Bank
    Bank *bank_;
    //Wskaźnik na obiekt klasy ClientManager
    ClientManager *clientManager_;
};

#endif // LOGIN_H
