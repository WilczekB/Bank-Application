
#include "emailsender.h"
#include <QtNetwork>
#include <QtDebug>
#include <cstdlib>
#include <ctime>

/*
 * Konstruktor
 */
EmailSender::EmailSender(QObject *parent) : QObject(parent)
{

}

void EmailSender::setVerificationCode()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    code = std::rand() % 90 + 10;

}

int EmailSender::getVerificationCode()
{
    return code;
}

/*
 * Funkcja wysyłająca powiadomienie mailowe
 */
void EmailSender::send()
{

    setVerificationCode();

    //Ustawienie treści tytułu i zawartości maila
    QString subject = "Weryfikacja do rejestracji konta bankowego";
    QString body = "Oto Twój jednorazowy kod weryfikacyjny: " + QString::number(code) + "." + " Potwierdź swoją rejestrację, podając swój kod w aplikacji.";

    //Konfiguracja klienta SMTP
    QSslSocket socket;
    socket.connectToHostEncrypted("smtp.gmail.com", 465);

    if(!socket.waitForConnected())
    {
        qWarning() << "Nie udalo sie polaczyc z serwerem SMTP";
        return;
    }

    auto tlsConfig = QSslConfiguration::defaultConfiguration();
    tlsConfig.setProtocol(QSsl::TlsV1_2);
    socket.setSslConfiguration(tlsConfig);

    if(!socket.waitForEncrypted())
    {
        qWarning() << "Nie udalo sie utworzyc polaczenia TLS";
        return;
    }

    //Logowanie się do serwera SMTP
    QTextStream in(&socket);
    QTextStream out(&socket);

    in.readLine();
    out << "EHLO example.com\r\n";

    in.readLine();
    out << "AUTH LOGIN\r\n";

    in.readLine();
    out << QByteArray().append("YmFydGVrd2lsY3plazlAZ21haWwuY29t") << "\r\n";

    in.readLine();
    out << QByteArray().append("Qnc3OTA1ODAwMzI=") << "\r\n";
    in.readLine();

    //Wysyłanie wiadomości e-mail
    out << "MAIL FROM: <example@example.com>\r\n";
    in.readLine();
    out << "RCPT TO: <bartekwilczek9@gmail.com>\r\n";
    in.readLine();
    out << "DATA\r\n";
    in.readLine();
    out << "FROM: Example <example@example.com>\r\n";
    out << "TO: Bartosz Wilczek <bartekwilczek9@gmail.com>\r\n";
    out << "SUBJECT: " << subject << "\r\n";
    out << "\r\n";
    out << body << "\r\n";
    out << ".\r\n";
    in.readLine();

    //Wylogowanie się z serwera SMTP
    out << "QUIT\r\n";
    in.readLine();

    //Zamknięcie połączenia
    socket.close();

}
