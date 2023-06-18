
#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <string>
#include <QtNetwork>

class EmailSender : public QObject
{
    Q_OBJECT

public:
    //Konstruktor
    EmailSender(QObject* parent = nullptr);

public slots:
    //Slot służący do wysyłania wiadomości email
    void send();
    //Slot służący do ustawienia wartości kodu weryfikacyjnego
    void setVerificationCode();
    //Slot zwracający wartość kodu weryfikacyjnego
    int getVerificationCode();

private:
    //Pole przechowujące wartość kodu weryfikacyjnego
    int code;

};

#endif // EMAILSENDER_H
