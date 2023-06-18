#ifndef VERIFYPINWINDOW_H
#define VERIFYPINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"

namespace Ui {
class verifyPINWindow;
}

class verifyPINWindow : public QDialog
{
    Q_OBJECT

public:
    explicit verifyPINWindow(QWidget *parent = nullptr, Client *client = nullptr);
    ~verifyPINWindow();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::verifyPINWindow *ui;
    Client *client_;
};

#endif // VERIFYPINWINDOW_H
