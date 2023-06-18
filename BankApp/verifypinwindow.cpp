#include "verifypinwindow.h"
#include "ui_verifypinwindow.h"


verifyPINWindow::verifyPINWindow(QWidget *parent, Client *client) :
    QDialog(parent),
    ui(new Ui::verifyPINWindow)
{
    ui->setupUi(this);

    client_ = client;
}

verifyPINWindow::~verifyPINWindow()
{
    delete client_;
    delete ui;
}

void verifyPINWindow::on_confirmButton_clicked()
{
    //Pobranie wartości kodu PIN wprowadzonej użytkownika
    int pinCode = ui->pinInput->text().toInt();

    //Sprawdzenie poprawności kodu PIN
    if(client_->verifyPIN(pinCode))
    {
        QMessageBox::information(this, "Potwierdzenie", "Udało się zweryfikować kod PIN");

    }

}

