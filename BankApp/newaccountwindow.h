#ifndef NEWACCOUNTWINDOW_H
#define NEWACCOUNTWINDOW_H

#include <QDialog>
#include "client.h"
#include "accountmanager.h"

namespace Ui {
class NewAccountWindow;
}

class NewAccountWindow : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param client wskaźnik do obiektu klasy Client
    explicit NewAccountWindow(QWidget *parent = nullptr, Client *client = nullptr);
    //Destruktor
    ~NewAccountWindow();

private slots:
    //Slot realizujący utworzenie nowego konta dla rejestrującego się użytkownika
    void on_createAccountButton_clicked();

    //Slot realizujący zamknięcie interfejsu NewAccountWindow
    void on_exitButton_clicked();

private:
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::NewAccountWindow *ui;
    //Wskaźnik na obiekt klasy Client
    Client *client_;
    //Wskaźnik na obiekt klasy AccountManager
    AccountManager *accountManager;
};

#endif // NEWACCOUNTWINDOW_H
