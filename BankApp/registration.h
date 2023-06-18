#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "login.h"
#include "bank.h"
#include "clientmanager.h"
#include <QMessageBox>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param bank wskaźnik do obiektu klasy Bank
    explicit Registration(QWidget *parent = nullptr, Bank *bank = nullptr);
    //Destruktor
    ~Registration();

private slots:
    //Slot realizujący rejestrację nowego użytkownika systemu bankowego
    void on_registerButton_clicked();

    //Slot realizujący zamknięcie interfejsu Registration
    void on_quitButton_clicked();

private:
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::Registration *ui;
    //Wskaźnik na obiekt klasy Bank
    Bank *bank_;
    //Wskaźnik na obiekt ClientManager
    ClientManager *clientManager_;
    //Wskaźnik na obiekt Login
    Login *loginWindow;
};

#endif // REGISTRATION_H
