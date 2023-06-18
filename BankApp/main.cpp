#include <QApplication>
#include "login.h"
#include "bank.h"

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    //Utworzenie nowego obiektu typu Bank
    Bank *bank = new Bank();

    //Utworzenie nowego obiektu typu Login
    Login *loginWindow = new Login(nullptr, bank);

    //Wyświetlenie okna logowania
    loginWindow->show();

    return a.exec();
}
