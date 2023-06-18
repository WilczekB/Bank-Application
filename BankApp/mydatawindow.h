#ifndef MYDATAWINDOW_H
#define MYDATAWINDOW_H

#include <QDialog>
#include "client.h"
#include "clientmanager.h"
#include <QMessageBox>

namespace Ui {
class MyDataWindow;
}

class MyDataWindow : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param client wskaźnik do obiektu klasy Client
    //@param clientManager wskaźnik do obiektu klasy clientManager
    explicit MyDataWindow(QWidget *parent = nullptr, Client* client = nullptr, ClientManager *clientManager = nullptr);
    //Destruktor
    ~MyDataWindow();

private slots:
    //Slot realizujący zaktualizowanie danych osobowych użytkownika
    void on_changeButton_clicked();

    //Slot realizujący zamknięcie interfejsu MyDataWindow
    void on_exitButton_clicked();

private:
    //Funkcja ustawiająca w polach tekstowych dane osobowe użytkownika
    void setMyData();
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::MyDataWindow *ui;
    //Wskaźnik na obiekt klasy Client
    Client* client_;
    //Wskaźnik na obiekt klasy ClientManager
    ClientManager* clientManager_;
};

#endif // MYDATAWINDOW_H
