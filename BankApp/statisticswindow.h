#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>
#include "accountmanager.h"


namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    //Konstruktor
    //@param parent wskaźnik do obiektu bazowego
    //@param accountManager wskaźnik do obiektu klasy AccountManager
    explicit StatisticsWindow(QWidget *parent = nullptr, AccountManager *accountManager = nullptr);
    //Destruktor
    ~StatisticsWindow();

private slots:
    //Slot realizujący zamknięcie interfejsu StatisticsWindow
    void on_gobackButton_clicked();

private:
    //Funkcja ustawiająca statystyki dotyczące danego konta
    void showStats();
    //Wskaźnik na obiekt reprezentujący interfejs użytkownika UI
    Ui::StatisticsWindow *ui;
    //Wskaźnik na obiekt klasy AccountManager
    AccountManager *accountManager_;
};

#endif // STATISTICSWINDOW_H
